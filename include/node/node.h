#pragma once
#include "core/helper.h"
#include "node/accelerator.h"
#include "node/application.h"
#include "node/communicator.h"
#include "ns3/ptr.h"
#include "utils/configuration.h"
#include "core/barrier.h"

namespace adpart_sim {

class Node : public INodeHelper {
   public:
    explicit Node(Core* parent, size_t node_id, std::shared_ptr<NodeMetadata> metadata);

   public:
    bool CheckResult();
    void InitializeNode();
    void SetTotalEpoch(size_t tota_epoch);

   public:
    size_t GetTraffic(size_t node_id);
    size_t GetTotalSendSizeByte();
    std::string GetTotalSendSizeStr();
    size_t GetTotalRecvSizeByte();
    std::string GetTotalRecvSizeStr();

   public:
    // m_application
    std::shared_ptr<NodeMetadata> get_metadata();
    size_t get_tasks_count();
    void clear_tasks();
    void add_task(std::shared_ptr<Task> task);
    std::shared_ptr<Task> get_task(size_t id);
    std::unordered_map<size_t, std::shared_ptr<Task>>& get_tasks();

   private:
    ns3::Ptr<Application> m_application = nullptr;
};

}  // namespace adpart_sim