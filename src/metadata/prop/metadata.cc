#include "metadata/metadata.h"

using namespace std;

namespace adpart_sim {

// m_parent
Core* Metadata::get_parent() { return m_parent; }

// m_mdata_strategy
shared_ptr<StrategyMetadata> Metadata::get_mdata_strategy() { return m_mdata_strategy; }

// m_mdata_node
shared_ptr<NodeMetadata> Metadata::get_mdata_node() { return m_mdata_node; }

// m_mdata_switch
shared_ptr<SwitchMetadata> Metadata::get_mdata_switch() { return m_mdata_switch; }

// m_mdata_networks
vector<shared_ptr<NetworkMetadata>>& Metadata::get_mdata_networks() { return m_mdata_networks; }

shared_ptr<NetworkMetadata> Metadata::get_mdata_network(size_t id) {
    LOGE_IF(id > m_mdata_networks.size() - 1, "out of index");
    return m_mdata_networks[id];
}

size_t Metadata::get_mdata_networks_count() { return m_mdata_networks.size(); }

}  // namespace adpart_sim