#include "node/application.h"
#include "core/core.h"
#include "core/result.h"
#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

Application::Application(Node *parent, shared_ptr<NodeMetadata> metadata) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_metadata
    m_metadata = metadata;
    // m_accelerators
    m_accelerator = make_shared<Accelerator>(this, m_metadata->get_mdata_accelerator());
}

bool Application::CheckResult(size_t total_send_size_byte, size_t total_recv_size_byte) {
    __TRACE_LOG__
    bool result = true;
    size_t compute_time_ns = 0;
    size_t communication_time_ns = 0;
    size_t compute_finish_time_ns = 0;
    size_t global_finish_time_ns = 0;
    size_t explosed_comm_ns = 0;
    map<TaskType, size_t> summary_result = {};
    vector<shared_ptr<Task>> tasks = {};
    for (auto &task_it : m_tasks) tasks.push_back(task_it.second);
    sort(tasks.begin(), tasks.end(), [](shared_ptr<Task> a_task, shared_ptr<Task> b_task) -> bool {
        return a_task->get_start_time_ns() < b_task->get_start_time_ns();
    });
    for (auto &task_it : tasks) {
        bool result_it = task_it->get_status() == TaskStatus::COMPLETED;
        LOGW_IF(!result_it, "task " << task_it->get_task_name() << " not completed");
        result = result && result_it;
        switch (task_it->get_type()) {
            case TaskType::COMPUTE:
                compute_time_ns += task_it->get_duration_time_ns();
                explosed_comm_ns += task_it->get_start_time_ns() - compute_finish_time_ns;
                compute_finish_time_ns = task_it->get_start_time_ns() + task_it->get_duration_time_ns();
                break;
            case TaskType::COMMUNICATION:
                communication_time_ns += task_it->get_duration_time_ns();
                break;
            default:
                LOGW("unprocess task type");
                break;
        }
        if (!result_it) Result::PrintDetail(task_it, _MAX_SIZE_T_);
        global_finish_time_ns = task_it->get_start_time_ns() + task_it->get_duration_time_ns();
    }
    explosed_comm_ns += global_finish_time_ns - compute_finish_time_ns;
    g_configuration->summary_file << m_parent->get_node_id() << ","               // node_id
                                  << compute_time_ns << ","                       // compute_time_ns
                                  << GetTimeStr(compute_time_ns) << ","           // compute_time_str
                                  << communication_time_ns << ","                 // communication_time_ns
                                  << GetTimeStr(communication_time_ns) << ","     // communication_time_str
                                  << explosed_comm_ns << ","                      // explosed_communication_ns
                                  << GetTimeStr(explosed_comm_ns) << ","          // explosed_communication_str
                                  << total_send_size_byte << ","                  // total_send_size_byte
                                  << GetSizeStr(total_send_size_byte) << ","      // total_send_size_str
                                  << total_recv_size_byte << ","                  // total_recv_size_byte
                                  << GetSizeStr(total_recv_size_byte) << ","      // total_recv_size_str
                                  << (result ? "SUCCESSFUL" : "FAILED") << "\n";  // check_result
    return result;
}

void Application::SetTotalEpoch(size_t total_epoch) {
    __TRACE_LOG__
    m_total_epoch = total_epoch;
    m_current_task_index = 0;
    for (auto &item : m_tasks) item.second->Reset();
}

void Application::Setup(unordered_map<size_t, vector<shared_ptr<Device>>> devices) {
    __TRACE_LOG__
    // m_communicator
    ASSERT(m_parent);
    ASSERT(m_parent->get_parent());
    shared_ptr<CommunicatorMetadata> mdata_communicator = m_metadata->get_mdata_communicator();
    unordered_map<shared_ptr<Network>, vector<shared_ptr<Device>>> networks;
    for (auto &device_it : devices) {
        size_t network_id = device_it.first;
        shared_ptr<Network> network = m_parent->get_parent()->get_network(network_id);
        networks[network] = device_it.second;
    }
    m_communicator = make_shared<Communicator>(this, mdata_communicator, networks);
}

vector<shared_ptr<Task>> Application::GetNextTask(shared_ptr<Task> task) {
    __TRACE_LOG__
    vector<shared_ptr<Task>> task_list;
    if (task == nullptr) SetTotalEpoch(m_total_epoch);
    if (task != nullptr) {
        task->Stop(m_current_epoch + 1);
        Result::PrintTrace(task);
        Result::PrintDetail(task, m_current_epoch + 1);
    }
    for (auto &task_it : m_tasks) {
        bool is_ready = task_it.second->get_status() == TaskStatus::READY;
        for (auto &parent_task_it : task_it.second->get_parent_tasks()) {
            is_ready = is_ready && parent_task_it->get_status() == TaskStatus::COMPLETED;
        }
        if (is_ready) {
            m_current_task_index++;
            task_list.push_back(task_it.second);
            task_it.second->Start();
        }
    }
    if (task_list.size() <= 0) {
        bool is_process_done = true;
        for (auto &item : m_tasks) {
            if (item.second->get_status() != TaskStatus::COMPLETED) {
                is_process_done = false;
                break;
            }
        }
        if (is_process_done && ++m_current_epoch < m_total_epoch) task_list = GetNextTask(nullptr);
    }
    return task_list;
}

}  // namespace adpart_sim