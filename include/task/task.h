#pragma once
#include "enum/enum.h"
#include "task/communication.h"
#include "task/compute.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Task {
   public:
    explicit Task(size_t node_id, size_t task_id, std::string task_name, TaskType type);

   public:
    void SetupTask(std::shared_ptr<ComputeTask> compute_task);
    void SetupTask(std::shared_ptr<CommunicationTask> communication_task);

   public:
    void Reset();
    void Start();
    void Stop(size_t epoch);

   public:
    // m_node_id
    size_t get_node_id();
    // m_task_id
    size_t get_task_id();
    // m_type
    TaskType get_type();
    std::string get_type_str();
    // m_status
    TaskStatus get_status();
    std::string get_status_str();
    // m_start_time_ns
    size_t get_start_time_ns();
    std::string get_start_time_str();
    // m_duration_time_ns
    size_t get_duration_time_ns();
    std::string get_duration_time_str();
    // m_task_name
    std::string get_task_name();
    // m_compute_task
    std::shared_ptr<ComputeTask> get_compute_task();
    // m_communication_task
    std::shared_ptr<CommunicationTask> get_communication_task();
    // m_child_tasks
    size_t get_child_tasks_count();
    void add_child_task(std::shared_ptr<Task> task);
    void clear_child_tasks();
    std::unordered_set<std::shared_ptr<Task>> &get_child_tasks();
    // m_parent_tasks
    size_t get_parent_tasks_count();
    void add_parent_task(std::shared_ptr<Task> task);
    void clear_parent_tasks();
    std::unordered_set<std::shared_ptr<Task>> &get_parent_tasks();

   private:
    size_t m_node_id = _MAX_SIZE_T_;
    size_t m_task_id = _MAX_SIZE_T_;
    TaskType m_type = TaskType::INVALID;
    TaskStatus m_status = TaskStatus::READY;
    size_t m_start_time_ns = 0;
    size_t m_duration_time_ns = 0;
    std::string m_task_name = "empty_task_name";
    std::shared_ptr<ComputeTask> m_compute_task = nullptr;
    std::shared_ptr<CommunicationTask> m_communication_task = nullptr;
    std::unordered_set<std::shared_ptr<Task>> m_child_tasks;
    std::unordered_set<std::shared_ptr<Task>> m_parent_tasks;
};

}  // namespace adpart_sim