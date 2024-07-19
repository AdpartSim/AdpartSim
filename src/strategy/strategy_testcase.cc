#include "enum/enum.h"
#include "strategy/strategy.h"

using namespace std;

namespace adpart_sim {

class Strategy_TestCase : public IStrategy {
   public:
    explicit Strategy_TestCase(Core *parent, shared_ptr<StrategyMetadata> metadata) : IStrategy(parent, metadata) {
        __TRACE_LOG__
        shared_ptr<File> json_file = make_shared<File>(metadata->get_workload());
        JsonCpp json = JsonCpp::parse(json_file->GetContent());
        // m_start_size_byte
        Json::Parse(m_start_size_byte, json, "StartSizeByte");
        // m_end_size_byte
        Json::Parse(m_end_size_byte, json, "EndSizeByte");
        // m_step_factor
        Json::Parse(m_step_factor, json, "StepFactor");
        // m_communications
        for (auto &it : Json::Get(json, "Algorithms")) {
            m_communications.push_back(GetCommunicationType(it.get<string>()));
        }
    }

   private:
    shared_ptr<Task> AllToAllWorkload(shared_ptr<Task> parent_task,          //
                                      shared_ptr<Node> node,                 //
                                      size_t task_id,                        //
                                      CommunicationType communication_type,  //
                                      size_t size_byte) {
        shared_ptr<Task> task = make_shared<Task>(                                 //
            node->get_node_id(),                                                   // node_id
            task_id,                                                               // task_id
            GetCommunicationType(communication_type),                              // task_name
            TaskType::COMMUNICATION);                                              // type
        shared_ptr<CommunicationTask> comm_task = make_shared<CommunicationTask>(  //
            communication_type,                                                    // communication_type
            size_byte                                                              // size_byte
        );
        task->SetupTask(comm_task);
        if (parent_task != nullptr) {
            parent_task->add_child_task(task);
            task->add_parent_task(parent_task);
        }
        parent_task = task;
        node->add_task(task);
        return task;
    }

    shared_ptr<Task> OneToAllWorkload(shared_ptr<Task> parent_task,          //
                                      shared_ptr<Node> node,                 //
                                      size_t task_id,                        //
                                      CommunicationType communication_type,  //
                                      size_t size_byte,                      //
                                      size_t root) {
        shared_ptr<Task> task = make_shared<Task>(                                 //
            node->get_node_id(),                                                   // node_id
            task_id,                                                               // task_id
            GetCommunicationType(communication_type),                              // task_name
            TaskType::COMMUNICATION);                                              // type
        shared_ptr<CommunicationTask> comm_task = make_shared<CommunicationTask>(  //
            communication_type,                                                    // communication_type
            size_byte,                                                             // size_byte
            root                                                                   // root
        );
        task->SetupTask(comm_task);
        if (parent_task != nullptr) {
            parent_task->add_child_task(task);
            task->add_parent_task(parent_task);
        }
        parent_task = task;
        node->add_task(task);
        return task;
    }

    shared_ptr<Task> OneToOneWorkload(shared_ptr<Task> parent_task,          //
                                      shared_ptr<Node> node,                 //
                                      size_t task_id,                        //
                                      CommunicationType communication_type,  //
                                      size_t size_byte,                      //
                                      size_t src,                            //
                                      size_t dst) {
        shared_ptr<Task> task = make_shared<Task>(                                 //
            node->get_node_id(),                                                   // node_id
            task_id,                                                               // task_id
            GetCommunicationType(communication_type),                              // task_name
            TaskType::COMMUNICATION);                                              // type
        shared_ptr<CommunicationTask> comm_task = make_shared<CommunicationTask>(  //
            communication_type,                                                    // communication_type
            size_byte,                                                             // size_byte
            src,                                                                   // src
            dst                                                                    // dst
        );
        task->SetupTask(comm_task);
        if (parent_task != nullptr) {
            parent_task->add_child_task(task);
            task->add_parent_task(parent_task);
        }
        parent_task = task;
        node->add_task(task);
        return task;
    }

   public:
    void DistributeWorkload(unordered_map<size_t, shared_ptr<Node>> &nodes) override {
        __TRACE_LOG__
        size_t task_id = 0;
        LOGE_IF(m_step_factor < 1, "StepFactor need > 1");
        for (auto &node_it : nodes) m_node_parent_tasks[node_it.second] = nullptr;
        for (auto &communication_type : m_communications) {
            size_t current_size_byte = m_start_size_byte;
            while (current_size_byte <= m_end_size_byte) {
                if (IsAllToAll(communication_type)) {
                    for (auto &node_it : nodes) {
                        m_node_parent_tasks[node_it.second] = AllToAllWorkload(  //
                            m_node_parent_tasks[node_it.second],                 // parent_task
                            node_it.second,                                      // node
                            task_id++,                                           // task_id
                            communication_type,                                  // communication_type
                            current_size_byte);                                  // size_byte
                    }
                } else if (IsAllToOne(communication_type) || IsOneToAll(communication_type)) {
                    for (auto &node_it : nodes) {
                        m_node_parent_tasks[node_it.second] = OneToAllWorkload(  //
                            m_node_parent_tasks[node_it.second],                 // parent_task
                            node_it.second,                                      // node
                            task_id++,                                           // task_id
                            communication_type,                                  // communication_type
                            current_size_byte,                                   // size_byte
                            0);                                                  // root
                    }
                } else if (communication_type == CommunicationType::P2P_SEND) {
                    for (auto &node_i : nodes) {
                        for (auto &node_j : nodes) {
                            if (node_i.first == node_j.first) continue;
                            m_node_parent_tasks[node_i.second] = OneToOneWorkload(  //
                                m_node_parent_tasks[node_i.second],                 // parent_task
                                node_i.second,                                      // node
                                task_id++,                                          // task_id
                                CommunicationType::P2P_SEND,                        // communication_type
                                current_size_byte,                                  // size_byte
                                node_i.first,                                       // src
                                node_j.first);                                      // dst
                        }
                    }
                } else if (communication_type == CommunicationType::P2P_RECV) {
                    for (auto &node_i : nodes) {
                        for (auto &node_j : nodes) {
                            if (node_i.first == node_j.first) continue;
                            m_node_parent_tasks[node_i.second] = OneToOneWorkload(  //
                                m_node_parent_tasks[node_i.second],                 // parent_task
                                node_i.second,                                      // node
                                task_id++,                                          // task_id
                                CommunicationType::P2P_SEND,                        // communication_type
                                current_size_byte,                                  // size_byte
                                node_i.first,                                       // src
                                node_j.first);                                      // dst
                            m_node_parent_tasks[node_j.second] = OneToOneWorkload(  //
                                m_node_parent_tasks[node_j.second],                 // parent_task
                                node_j.second,                                      // node
                                task_id++,                                          // task_id
                                CommunicationType::P2P_RECV,                        // communication_type
                                current_size_byte,                                  // size_byte
                                node_j.first,                                       // src
                                node_i.first);                                      // dst
                            for (auto &node_k : nodes) {
                                m_node_parent_tasks[node_k.second] = AllToAllWorkload(  //
                                    m_node_parent_tasks[node_k.second],                 // parent_task
                                    node_k.second,                                      // node
                                    task_id++,                                          // task_id
                                    CommunicationType::BARRIER,                         // communication_type
                                    current_size_byte);                                 // size_byte
                            }
                        }
                    }
                } else {
                    LOGW("unhandled type: " << (int)communication_type);
                }
                current_size_byte *= m_step_factor;
            }
        }
    }

   private:
    size_t m_start_size_byte = 0;
    size_t m_end_size_byte = 0;
    size_t m_step_factor = 0;
    vector<CommunicationType> m_communications = {};
    unordered_map<shared_ptr<Node>, shared_ptr<Task>> m_node_parent_tasks = {};
};

}  // namespace adpart_sim