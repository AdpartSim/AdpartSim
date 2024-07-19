#include "task/task.h"
#include "core/result.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

Task::Task(size_t node_id, size_t task_id, string task_name, TaskType type) {
    __TRACE_LOG__
    m_node_id = node_id;
    m_task_id = task_id;
    m_task_name = task_name;
    m_type = type;
    m_compute_task = make_shared<ComputeTask>();
    m_communication_task = make_shared<CommunicationTask>();
}

void Task::SetupTask(shared_ptr<ComputeTask> compute_task) {
    __TRACE_LOG__
    m_compute_task = compute_task;
}

void Task::SetupTask(shared_ptr<CommunicationTask> communication_task) {
    __TRACE_LOG__
    m_communication_task = communication_task;
}

void Task::Reset() {
    __TRACE_LOG__
    m_start_time_ns = 0;
    m_duration_time_ns = 0;
    m_status = TaskStatus::READY;
}

void Task::Stop(size_t epoch) {
    __TRACE_LOG__
    LOGW_IF(m_status != TaskStatus::RUNNING, "task id: " << m_task_id << " status error");
    m_status = TaskStatus::COMPLETED;
    size_t stop_ns = ns3::Simulator::Now().GetNanoSeconds();
    m_duration_time_ns = stop_ns - m_start_time_ns;
}

void Task::Start() {
    __TRACE_LOG__
    LOGW_IF(m_status != TaskStatus::READY, "task id: " << m_task_id << " status error");
    m_status = TaskStatus::RUNNING;
    m_start_time_ns = ns3::Simulator::Now().GetNanoSeconds();
}

}  // namespace adpart_sim