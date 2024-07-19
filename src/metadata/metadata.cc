#include "metadata/metadata.h"

using namespace std;

namespace adpart_sim {

Metadata::Metadata(Core *parent, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_strategy
    m_mdata_strategy = make_shared<StrategyMetadata>(this, Json::Get(json, "Strategy"));
    // m_node
    m_mdata_node = make_shared<NodeMetadata>(this, Json::Get(json, "Node"));
    // m_switchs
    m_mdata_switch = make_shared<SwitchMetadata>(this, Json::Get(json, "Switch"));
    // m_network
    size_t network_id = 0;
    for (auto const &item : Json::Get(json, "Network")) {
        m_mdata_networks.push_back(make_shared<NetworkMetadata>(this, network_id++, item));
    }
    // check total node number and switch number
    size_t total_node_count = 0;
    size_t total_switch_count = 0;
    for (auto &network_it : m_mdata_networks) {
        total_node_count += network_it->get_repeat_count() * network_it->get_node_count();
        total_switch_count += network_it->get_repeat_count() * network_it->get_switch_count();
    }
    LOGE_IF(total_node_count != m_mdata_node->get_count(), "the count of node does not match network");
    LOGE_IF(total_switch_count != m_mdata_switch->get_count(), "the count of switch does not match network");
}

}  // namespace adpart_sim