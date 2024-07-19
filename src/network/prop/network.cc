#include "network/network.h"

using namespace std;

namespace adpart_sim {

// m_parent
Core *INetwork::get_parent() { return m_parent; }

// m_metadata
shared_ptr<NetworkMetadata> INetwork::get_metadata() { return m_metadata; }

// m_id
size_t INetwork::get_id() { return m_id; }

// m_barrier
std::shared_ptr<Barrier> INetwork::get_barrier() { return m_barrier; }

}  // namespace adpart_sim

namespace adpart_sim {

// m_type
NetworkType Network::get_type() { return m_type; }

string Network::get_type_str() { return GetNetworkType(m_type); }

// m_network
size_t Network::get_id() {
    ASSERT(m_network);
    return m_network->get_id();
}

Core *Network::get_parent() {
    ASSERT(m_network);
    return m_network->get_parent();
}

shared_ptr<INetwork> Network::get_network() { return m_network; }

shared_ptr<NetworkMetadata> Network::get_metadata() {
    ASSERT(m_network);
    return m_network->get_metadata();
}

}  // namespace adpart_sim