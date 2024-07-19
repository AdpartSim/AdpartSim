#include "enum/enum.h"
#include "et_feeder.h"
#include "strategy/strategy.h"

using namespace std;

using namespace ChakraProtoMsg;

namespace adpart_sim {

class Strategy_Chakra : public IStrategy {
   public:
    explicit Strategy_Chakra(Core *parent, shared_ptr<StrategyMetadata> metadata) : IStrategy(parent, metadata) {
        __TRACE_LOG__
        m_task_map = {
            {NodeType::COMP_NODE, TaskType::COMPUTE},
            {NodeType::COMM_SEND_NODE, TaskType::COMMUNICATION},
            {NodeType::COMM_RECV_NODE, TaskType::COMMUNICATION},
            {NodeType::COMM_COLL_NODE, TaskType::COMMUNICATION},
        };
        m_communication_map = {
            {CollectiveCommType::BARRIER, CommunicationType::BARRIER},
            {CollectiveCommType::REDUCE, CommunicationType::REDUCE},
            {CollectiveCommType::GATHER, CommunicationType::GATHER},
            {CollectiveCommType::SCATTER, CommunicationType::SCATTER},
            {CollectiveCommType::BROADCAST, CommunicationType::BROADCAST},
            {CollectiveCommType::ALL_TO_ALL, CommunicationType::ALL_TO_ALL},
            {CollectiveCommType::ALL_GATHER, CommunicationType::ALL_GATHER},
            {CollectiveCommType::ALL_REDUCE, CommunicationType::ALL_REDUCE},
            {CollectiveCommType::REDUCE_SCATTER, CommunicationType::REDUCE_SCATTER},
            {CollectiveCommType::REDUCE_SCATTER_BLOCK, CommunicationType::INVALID},

        };
    }

    void DistributeWorkload(unordered_map<size_t, shared_ptr<Node>> &nodes) override {
        __TRACE_LOG__
        for (auto &node_it : nodes) {
            size_t node_id = node_it.first;
            node_it.second->clear_tasks();
            map<shared_ptr<Task>, vector<shared_ptr<Chakra::ETFeederNode>>> child_tasks;
            File workload(m_metadata->get_workload() + "." + to_string(node_id) + ".et");
            LOGE_IF(!workload.exists(), workload.fullpath() << " not exist");
            shared_ptr<Chakra::ETFeeder> et_feeder = make_shared<Chakra::ETFeeder>(workload.fullpath());
            shared_ptr<Chakra::ETFeederNode> et_task = et_feeder->getNextIssuableNode();
            while (et_feeder->hasNodesToIssue() && et_task != nullptr) {
                // get the properties in et node
                size_t task_id = et_task->id();
                string task_name = et_task->name();
                LOGE_IF(m_task_map.count(et_task->type()) <= 0, "unregistered type");
                TaskType task_type = m_task_map[et_task->type()];
                shared_ptr<Task> task = make_shared<Task>(node_id, task_id, task_name, task_type);
                child_tasks[task] = et_task->getChildren();
                if (task_type == TaskType::COMPUTE) {
                    auto compute_task = make_shared<ComputeTask>(et_task->runtime() * 1000);
                    task->SetupTask(compute_task);
                } else if (task_type == TaskType::COMMUNICATION) {
                    CommunicationType comm_type = CommunicationType::INVALID;
                    if (et_task->type() == ChakraProtoMsg::NodeType::COMM_SEND_NODE)
                        comm_type = CommunicationType::P2P_SEND;
                    else if (et_task->type() == ChakraProtoMsg::NodeType::COMM_RECV_NODE)
                        comm_type = CommunicationType::P2P_RECV;
                    else if (m_communication_map.count(et_task->comm_type()) > 0)
                        comm_type = m_communication_map[et_task->comm_type()];
                    // chakra issues https://github.com/mlcommons/chakra/issues/136
                    // et_task->comm_size() error in tools/chakra/feeder/et_feeder_node.cpp:28
                    // need modify `this->comm_size_ = attr.int64_val();` to `this->comm_size_ = attr.uint64_val();`
                    shared_ptr<CommunicationTask> comm_task = std::make_shared<CommunicationTask>(  //
                        comm_type,             // communication_type
                        et_task->comm_size(),  // size_byte
                        0,                     // root
                        et_task->comm_src(),   // src
                        et_task->comm_dst());  // dst
                    task->SetupTask(comm_task);
                } else {
                    LOGE("unhandled Type");
                }
                node_it.second->add_task(task);
                // free et_task info and get new one
                et_feeder->freeChildrenNodes(task_id);
                et_feeder->removeNode(task_id);
                et_task = et_feeder->getNextIssuableNode();
            }
            // fill child task
            for (auto &task_it : child_tasks) {
                shared_ptr<Task> task = task_it.first;
                for (auto &child_task : task_it.second) {
                    size_t id = child_task->id();
                    task->add_child_task(node_it.second->get_task(id));
                }
            }
            // fill parent task
            for (auto &task_it : node_it.second->get_tasks()) {
                shared_ptr<Task> task = task_it.second;
                for (auto &child_task : task->get_child_tasks()) {
                    size_t id = child_task->get_task_id();
                    node_it.second->get_task(id)->add_parent_task(task);
                }
            }
        }
    }

   private:
    unordered_map<NodeType, TaskType> m_task_map;
    unordered_map<CollectiveCommType, CommunicationType> m_communication_map;
};

}  // namespace adpart_sim