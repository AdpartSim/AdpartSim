#include "node/algorithm.h"
#include "network/network.h"

using namespace std;

namespace adpart_sim {

// m_start_time_ns
size_t IAlgorithm::get_start_time_ns() { return m_start_time_ns; }

string IAlgorithm::get_start_time_str() { return GetTimeStr(m_start_time_ns); }

// m_parent
Communicator *IAlgorithm::get_parent() { return m_parent; }

// m_networks
unordered_map<shared_ptr<Network>, vector<shared_ptr<Device>>> IAlgorithm::get_networks() { return m_networks; }

size_t IAlgorithm::get_networks_count() { return m_networks.size(); }

vector<shared_ptr<Device>> IAlgorithm::get_devices(shared_ptr<Network> network) {
    LOGE_IF(m_networks.count(network) <= 0, "out of index");
    return m_networks[network];
}

size_t IAlgorithm::get_devices_count(shared_ptr<Network> network) { return get_devices(network).size(); }

vector<shared_ptr<Device>> IAlgorithm::get_devices(size_t network_id) {
    for (auto &network_it : m_networks) {
        if (network_it.first->get_id() == network_id) {
            return network_it.second;
        }
    }
    LOGE("out of index");
}

size_t IAlgorithm::get_devices_count(size_t network_id) { return get_devices(network_id).size(); }

// m_devices
shared_ptr<Device> IAlgorithm::get_device(size_t device_id) {
    LOGE_IF(m_devices.count(device_id) <= 0, "out of index");
    return m_devices[device_id];
}

// m_nodes
vector<shared_ptr<Network>> IAlgorithm::get_node_networks(size_t node_id) {
    LOGE_IF(m_nodes.count(node_id) <= 0, "out of index");
    return m_nodes[node_id];
}

shared_ptr<Network> IAlgorithm::get_node_network(size_t node_id) {
    vector<shared_ptr<Network>> networks = get_node_networks(node_id);
    return networks.size() > 0 ? networks[0] : nullptr;
}

}  // namespace adpart_sim

namespace adpart_sim {

// m_type
AlgorithmType Algorithm::get_type() { return m_type; }

string Algorithm::get_type_str() { return GetAlgorithmType(m_type); }

// m_algorithm
Communicator *Algorithm::get_parent() {
    ASSERT(m_algorithm);
    return m_algorithm->get_parent();
}

shared_ptr<IAlgorithm> Algorithm::get_algorithm() { return m_algorithm; }

}  // namespace adpart_sim