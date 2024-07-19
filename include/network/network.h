#pragma once
#include "core/barrier.h"
#include "enum/enum.h"
#include "metadata/network.h"
#include "network/topology.h"
#include "node/node.h"
#include "ns3/point-to-point-helper.h"
#include "switch/switch.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Core;

class INetwork {
   public:
    explicit INetwork(Core *parent, size_t id, std::shared_ptr<NetworkMetadata> metadata);

   public:
    virtual void BuildTopology(                     //
        std::vector<std::shared_ptr<Node>> &nodes,  //
        std::vector<std::shared_ptr<Switch>> &switchs)
        = 0;

   protected:
    void BuildTopology(                             //
        ns3::PointToPointHelper p2p,                //
        std::vector<std::shared_ptr<Node>> &nodes,  //
        std::vector<std::shared_ptr<Switch>> &switchs);

   public:
    // m_parent
    Core *get_parent();
    // m_metadata
    std::shared_ptr<NetworkMetadata> get_metadata();
    // m_id
    size_t get_id();
    // m_barrier
    std::shared_ptr<Barrier> get_barrier();

   private:
    Core *m_parent = nullptr;
    std::shared_ptr<NetworkMetadata> m_metadata = nullptr;
    size_t m_id = 0;
    std::shared_ptr<Barrier> m_barrier = nullptr;
};

}  // namespace adpart_sim

namespace adpart_sim {

class Network {
   public:
    explicit Network(Core *parent, size_t id, std::shared_ptr<NetworkMetadata> metadata);

   public:
    void BarrierClear();
    void BarrierWait(std::function<void()> callback);
    void BuildTopology(std::unordered_map<size_t, std::shared_ptr<Node>> &nodes,
                       std::unordered_map<size_t, std::shared_ptr<Switch>> &switchs);

   public:
    // m_type
    NetworkType get_type();
    std::string get_type_str();
    // m_network
    size_t get_id();
    Core *get_parent();
    std::shared_ptr<INetwork> get_network();
    std::shared_ptr<NetworkMetadata> get_metadata();

   private:
    NetworkType m_type = NetworkType::INVALID;
    std::shared_ptr<INetwork> m_network = nullptr;
};

}  // namespace adpart_sim
