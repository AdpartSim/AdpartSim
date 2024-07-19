#pragma once
#include "core/helper.h"
#include "enum/enum.h"
#include "metadata/communicator.h"
#include "node/algorithm.h"
#include "ns3/address.h"
#include "ns3/net-device.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "task/task.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Application;
class Network;

class Communicator {
   public:
    explicit Communicator(Application *parent,                             //
                          std::shared_ptr<CommunicatorMetadata> metadata,  //
                          std::unordered_map<std::shared_ptr<Network>, std::vector<std::shared_ptr<Device>>> networks);

   public:
    void Run(Application *caller,                                   //
             void (Application::*callback)(std::shared_ptr<Task>),  //
             std::shared_ptr<Task> task);

   private:
    void Callback(Application *caller,                                   //
                  void (Application::*callback)(std::shared_ptr<Task>),  //
                  std::shared_ptr<Task> task);

   public:
    // m_is_busy
    bool is_busy();
    // m_parent
    Application *get_parent();
    // m_metadata
    std::shared_ptr<CommunicatorMetadata> get_metadata();
    // m_algorithm
    std::shared_ptr<Algorithm> get_algorithm();

   private:
    bool m_is_busy = false;
    Application *m_parent = nullptr;
    std::shared_ptr<CommunicatorMetadata> m_metadata = nullptr;
    std::shared_ptr<Algorithm> m_algorithm = nullptr;
};

}  // namespace adpart_sim