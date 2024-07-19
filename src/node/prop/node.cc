#include "node/node.h"

using namespace std;

namespace adpart_sim {

// m_application
shared_ptr<NodeMetadata> Node::get_metadata() {
    ASSERT(m_application);
    return m_application->get_metadata();
}

size_t Node::get_tasks_count() {
    ASSERT(m_application);
    return m_application->get_tasks_count();
}

void Node::clear_tasks() {
    ASSERT(m_application);
    return m_application->clear_tasks();
}

void Node::add_task(shared_ptr<Task> task) {
    ASSERT(m_application);
    return m_application->add_task(task);
}

shared_ptr<Task> Node::get_task(size_t id) {
    ASSERT(m_application);
    return m_application->get_task(id);
}

unordered_map<size_t, shared_ptr<Task>> &Node::get_tasks() {
    ASSERT(m_application);
    return m_application->get_tasks();
}

}  // namespace adpart_sim