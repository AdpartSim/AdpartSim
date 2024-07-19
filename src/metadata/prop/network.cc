#include "metadata/network.h"

using namespace std;

namespace adpart_sim {

// m_parent
Metadata *NetworkMetadata::get_parent() { return m_parent; }

// m_id
size_t NetworkMetadata::get_id() { return m_id; }

// m_network_type
NetworkType NetworkMetadata::get_network_type() { return m_network_type; }

string NetworkMetadata::get_network_type_str() { return GetNetworkType(m_network_type); }

// m_topology_type
TopologyType NetworkMetadata::get_topology_type() { return m_topology_type; }

string NetworkMetadata::get_topology_type_str() { return GetTopologyType(m_topology_type); }

// m_topology_attrs
vector<size_t> NetworkMetadata::get_topology_attrs() { return m_topology_attrs; }

size_t NetworkMetadata::get_topology_attr(size_t id) {
    LOGE_IF(id > m_topology_attrs.size() - 1, "out of index");
    return m_topology_attrs[id];
}
size_t NetworkMetadata::get_topology_attrs_count() { return m_topology_attrs.size(); }

// m_node_count
size_t NetworkMetadata::get_node_count() { return m_node_count; }

// m_switch_count
size_t NetworkMetadata::get_switch_count() { return m_switch_count; }

// m_repeat_count
size_t NetworkMetadata::get_repeat_count() { return m_repeat_count; }

// m_bandwidth_gbps
double NetworkMetadata::get_bandwidth_gbps() { return m_bandwidth_gbps; }

string NetworkMetadata::get_bandwidth_str() { return GetBandwidthStr(m_bandwidth_gbps); }

// m_latency_ns
size_t NetworkMetadata::get_latency_ns() { return m_latency_ns; }

string NetworkMetadata::get_latency_str() { return GetTimeStr(m_latency_ns); }

}  // namespace adpart_sim