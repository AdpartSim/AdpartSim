#include "core/core.h"

using namespace std;

namespace adpart_sim {

// m_mdata
shared_ptr<Metadata> Core::get_mdata() { return m_mdata; }

// m_strategy
shared_ptr<Strategy> Core::get_strategy() { return m_strategy; }

// m_nodes
std::unordered_map<size_t, shared_ptr<Node>> &Core::get_nodes() { return m_nodes; }

shared_ptr<Node> Core::get_node(size_t id) {
    LOGE_IF(m_nodes.count(id) <= 0, "out of index");
    return m_nodes[id];
}

size_t Core::get_nodes_count() { return m_nodes.size(); }

// m_switchs
std::unordered_map<size_t, shared_ptr<Switch>> &Core::get_switchs() { return m_switchs; }

shared_ptr<Switch> Core::get_switch(size_t id) {
    LOGE_IF(m_switchs.count(id) <= 0, "out of index");
    return m_switchs[id];
}

size_t Core::get_switchs_count() { return m_switchs.size(); }

// m_networks
std::unordered_map<size_t, shared_ptr<Network>> &Core::get_networks() { return m_networks; }

shared_ptr<Network> Core::get_network(size_t id) {
    LOGE_IF(m_networks.count(id) <= 0, "out of index");
    return m_networks[id];
}

size_t Core::get_networks_count() { return m_networks.size(); }

}  // namespace adpart_sim
