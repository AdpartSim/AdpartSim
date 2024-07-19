#pragma once
#include "core/barrier.h"
#include "enum/enum.h"
#include "metadata/node.h"
#include "node/accelerator.h"
#include "node/communicator.h"
#include "ns3/application.h"
#include "ns3/net-device.h"
#include "ns3/ptr.h"
#include "task/task.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Node;

class Application : public ns3::Application {
   public:
    explicit Application(Node *parent, std::shared_ptr<NodeMetadata> metadata);

   public:
    void SetTotalEpoch(size_t total_epoch);
    bool CheckResult(size_t total_send_size_byte, size_t total_recv_size_byte);
    void Setup(std::unordered_map<size_t, std::vector<std::shared_ptr<Device>>> devices);

   protected:
    virtual void StartApplication();
    virtual void StopApplication();

   private:
    void DoNextTask(std::shared_ptr<Task> task);
    std::vector<std::shared_ptr<Task>> GetNextTask(std::shared_ptr<Task> task);

   public:
    // m_parent
    Node *get_parent();
    // m_metadata
    std::shared_ptr<NodeMetadata> get_metadata();
    // m_accelerator
    std::shared_ptr<Accelerator> get_accelerator();
    // m_communicator
    std::shared_ptr<Communicator> get_communicator();
    // m_current_epoch
    size_t get_current_epoch();
    // m_total_epoch
    size_t get_total_epoch();
    // m_task_index
    size_t get_current_task_index();
    // m_tasks
    size_t get_tasks_count();
    void clear_tasks();
    void add_task(std::shared_ptr<Task> task);
    std::shared_ptr<Task> get_task(size_t id);
    std::unordered_map<size_t, std::shared_ptr<Task>> &get_tasks();

   private:
    Node *m_parent = nullptr;
    std::shared_ptr<NodeMetadata> m_metadata = nullptr;
    std::shared_ptr<Accelerator> m_accelerator = nullptr;
    std::shared_ptr<Communicator> m_communicator = nullptr;
    size_t m_current_epoch = 0;
    size_t m_total_epoch = 0;
    size_t m_current_task_index = 0;
    std::unordered_map<size_t, std::shared_ptr<Task>> m_tasks = {};
};

}  // namespace adpart_sim