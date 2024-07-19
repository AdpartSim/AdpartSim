#include "task/task.h"

using namespace std;

namespace adpart_sim {

// m_node_id
size_t Task::get_node_id() { return m_node_id; }

// m_task_id
size_t Task::get_task_id() { return m_task_id; }

// m_type
TaskType Task::get_type() { return m_type; }

string Task::get_type_str() { return GetTaskType(m_type); }

// m_status
TaskStatus Task::get_status() { return m_status; }

string Task::get_status_str() { return GetTaskStatus(m_status); }

// m_start_time_ns
size_t Task::get_start_time_ns() { return m_start_time_ns; }

string Task::get_start_time_str() { return GetTimeStr(m_start_time_ns); }

// m_duration_time_ns
size_t Task::get_duration_time_ns() { return m_duration_time_ns; }

string Task::get_duration_time_str() { return GetTimeStr(m_duration_time_ns); }

// m_task_name
string Task::get_task_name() { return m_task_name; }

// m_compute_task
shared_ptr<ComputeTask> Task::get_compute_task() { return m_compute_task; }

// m_communication_task
shared_ptr<CommunicationTask> Task::get_communication_task() { return m_communication_task; }

// m_child_tasks
size_t Task::get_child_tasks_count() { return m_child_tasks.size(); }

void Task::add_child_task(shared_ptr<Task> task) { m_child_tasks.emplace(task); }

void Task::clear_child_tasks() { m_child_tasks.clear(); }

unordered_set<shared_ptr<Task>>& Task::get_child_tasks() { return m_child_tasks; }

// m_parent_tasks
size_t Task::get_parent_tasks_count() { return m_parent_tasks.size(); }

void Task::add_parent_task(shared_ptr<Task> task) { m_parent_tasks.emplace(task); }

void Task::clear_parent_tasks() { m_parent_tasks.clear(); }

unordered_set<shared_ptr<Task>>& Task::get_parent_tasks() { return m_parent_tasks; }

}  // namespace adpart_sim