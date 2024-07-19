#include "metadata/memory.h"

using namespace std;

namespace adpart_sim {

// m_parent
NodeMetadata *MemoryMetadata::get_parent() { return m_parent; }

// m_latency_ns
size_t MemoryMetadata::get_latency_ns() { return m_latency_ns; }

string MemoryMetadata::get_latency_str() { return GetTimeStr(m_latency_ns); }

// m_bandwidth_gbps
double MemoryMetadata::get_bandwidth_gbps() { return m_bandwidth_gbps; }

string MemoryMetadata::get_bandwidth_str() { return GetBandwidthStr(m_bandwidth_gbps); }

// m_capacity_gb
double MemoryMetadata::get_capacity_gb() { return m_capacity_gb; }

string MemoryMetadata::get_capacity_str() { return GetSizeStr(m_capacity_gb * 1000000000); }

}  // namespace adpart_sim