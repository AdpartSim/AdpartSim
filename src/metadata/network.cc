#include "metadata/network.h"

using namespace std;

namespace adpart_sim {

NetworkMetadata::NetworkMetadata(Metadata *parent, size_t id, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_id
    m_id = id;
    // m_network_type
    m_network_type = GetNetworkType(Json::GetStr(json, "Type"));
    // m_topology_type
    m_topology_type = GetTopologyType(Json::GetStr(json, "Topology"));
    // m_topology_attrs
    Json::Parse(m_topology_attrs, json, "TopologyAttrs");
    // m_node_count
    Json::Parse(m_node_count, json, "NodeCount");
    // m_switch_count
    Json::Parse(m_switch_count, json, "SwitchCount");
    // m_repeat_count
    Json::Parse(m_repeat_count, json, "RepeatCount");
    // m_bandwidth_gbps
    Json::Parse(m_bandwidth_gbps, json, "Bandwidth_Gbps");
    // m_latency_ns
    Json::Parse(m_latency_ns, json, "Latency_ns");
}

}  // namespace adpart_sim