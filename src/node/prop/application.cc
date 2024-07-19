#include "node/application.h"

using namespace std;

namespace adpart_sim {

// m_parent
Node* Application::get_parent() { return m_parent; }

// m_metadata
shared_ptr<NodeMetadata> Application::get_metadata() { return m_metadata; }

// m_accelerators
shared_ptr<Accelerator> Application::get_accelerator() { return m_accelerator; }

// m_communicator
shared_ptr<Communicator> Application::get_communicator() { return m_communicator; }

// m_current_epoch
size_t Application::get_current_epoch() { return m_current_epoch; }

// m_total_epoch
size_t Application::get_total_epoch() { return m_total_epoch; }

// m_task_index
size_t Application::get_current_task_index() { return m_current_task_index; }

// m_tasks
size_t Application::get_tasks_count() { return m_tasks.size(); }

void Application::clear_tasks() { m_tasks.clear(); }

void Application::add_task(shared_ptr<Task> task) {
    LOGE_IF(m_tasks.count(task->get_task_id()), "duplicate id");
    m_tasks[task->get_task_id()] = task;
}

shared_ptr<Task> Application::get_task(size_t id) {
    if (m_tasks.count(id) > 0) return m_tasks[id];
    LOGE("id not found");
}

unordered_map<size_t, shared_ptr<Task>>& Application::get_tasks() { return m_tasks; }

}  // namespace adpart_sim
