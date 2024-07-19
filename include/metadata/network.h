#pragma once
#include "enum/enum.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Metadata;

class NetworkMetadata {
   public:
    explicit NetworkMetadata(Metadata *parent, size_t id, JsonCpp const &json);

   public:
    // m_parent
    Metadata *get_parent();
    // m_id
    size_t get_id();
    // m_network_type
    NetworkType get_network_type();
    std::string get_network_type_str();
    // m_topology_type
    TopologyType get_topology_type();
    std::string get_topology_type_str();
    // m_topology_attrs
    std::vector<size_t> get_topology_attrs();
    size_t get_topology_attr(size_t id);
    size_t get_topology_attrs_count();
    // m_node_count
    size_t get_node_count();
    // m_switch_count
    size_t get_switch_count();
    // m_repeat_count
    size_t get_repeat_count();
    // m_bandwidth_gbps
    double get_bandwidth_gbps();
    std::string get_bandwidth_str();
    // m_latency_ns
    size_t get_latency_ns();
    std::string get_latency_str();

   private:
    Metadata *m_parent = nullptr;
    size_t m_id = 0;
    NetworkType m_network_type = NetworkType::INVALID;
    TopologyType m_topology_type = TopologyType::INVALID;
    std::vector<size_t> m_topology_attrs = {};
    size_t m_node_count = 0;
    size_t m_switch_count = 0;
    size_t m_repeat_count = 0;
    double m_bandwidth_gbps = 0;
    size_t m_latency_ns = 0;
};

}  // namespace adpart_sim
