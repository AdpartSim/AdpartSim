#pragma once
#include "metadata/metadata.h"
#include "network/network.h"
#include "node/node.h"
#include "strategy/strategy.h"
#include "switch/switch.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Core {
   public:
    explicit Core();

   public:
    void SetupSimulator();
    void RunSimulator();

   public:
    // m_mdata
    std::shared_ptr<Metadata> get_mdata();
    // m_strategy
    std::shared_ptr<Strategy> get_strategy();
    // m_nodes
    std::unordered_map<size_t, std::shared_ptr<Node>> &get_nodes();
    std::shared_ptr<Node> get_node(size_t id);
    size_t get_nodes_count();
    // m_switchs
    std::unordered_map<size_t, std::shared_ptr<Switch>> &get_switchs();
    std::shared_ptr<Switch> get_switch(size_t id);
    size_t get_switchs_count();
    // m_networks
    std::unordered_map<size_t, std::shared_ptr<Network>> &get_networks();
    std::shared_ptr<Network> get_network(size_t id);
    size_t get_networks_count();

   private:
    std::shared_ptr<Metadata> m_mdata = nullptr;
    std::shared_ptr<Strategy> m_strategy = nullptr;
    std::unordered_map<size_t, std::shared_ptr<Node>> m_nodes = {};
    std::unordered_map<size_t, std::shared_ptr<Switch>> m_switchs = {};
    std::unordered_map<size_t, std::shared_ptr<Network>> m_networks = {};
};

}  // namespace adpart_sim
