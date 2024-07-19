#pragma once
#include "metadata/network.h"
#include "metadata/node.h"
#include "metadata/strategy.h"
#include "metadata/switch.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Core;

class Metadata {
   public:
    explicit Metadata(Core *parent, JsonCpp const &json);

   public:
    // m_parent
    Core *get_parent();
    // m_mdata_strategy
    std::shared_ptr<StrategyMetadata> get_mdata_strategy();
    // m_mdata_node
    std::shared_ptr<NodeMetadata> get_mdata_node();
    // m_mdata_switch
    std::shared_ptr<SwitchMetadata> get_mdata_switch();
    // m_mdata_networks
    std::vector<std::shared_ptr<NetworkMetadata>> &get_mdata_networks();
    std::shared_ptr<NetworkMetadata> get_mdata_network(size_t id);
    size_t get_mdata_networks_count();

   private:
    Core *m_parent = nullptr;
    std::shared_ptr<StrategyMetadata> m_mdata_strategy = nullptr;
    std::shared_ptr<NodeMetadata> m_mdata_node = nullptr;
    std::shared_ptr<SwitchMetadata> m_mdata_switch = nullptr;
    std::vector<std::shared_ptr<NetworkMetadata>> m_mdata_networks = {};
};

}  // namespace adpart_sim
