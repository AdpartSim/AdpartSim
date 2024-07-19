#include "metadata/memory.h"

using namespace std;

namespace adpart_sim {

MemoryMetadata::MemoryMetadata(NodeMetadata *parent, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_bandwidth_gbps
    Json::Parse(m_bandwidth_gbps, json, "Bandwidth_Gbps");
    // m_latency_ns
    Json::Parse(m_latency_ns, json, "Latency_ns");
    // m_capacity_gb
    Json::Parse(m_capacity_gb, json, "Capacity_GB");
}

}  // namespace adpart_sim