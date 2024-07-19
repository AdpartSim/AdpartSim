#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

class NodeMetadata;

class MemoryMetadata {
   public:
    explicit MemoryMetadata(NodeMetadata *parent, JsonCpp const &json);

   public:
    NodeMetadata *get_parent();
    // m_latency_ns
    size_t get_latency_ns();
    std::string get_latency_str();
    // m_bandwidth_gbps
    double get_bandwidth_gbps();
    std::string get_bandwidth_str();
    // m_capacity_gb
    double get_capacity_gb();
    std::string get_capacity_str();

   private:
    NodeMetadata *m_parent = nullptr;
    size_t m_latency_ns = 0;
    double m_bandwidth_gbps = 0;
    double m_capacity_gb = 0;
};

}  // namespace adpart_sim
