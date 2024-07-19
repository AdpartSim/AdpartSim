#include "network/network.h"
#include "network_ethernet.cc"
#include "network_phy.cc"

using namespace std;

namespace adpart_sim {

INetwork::INetwork(Core *parent, size_t id, shared_ptr<NetworkMetadata> metadata) {
    __TRACE_LOG__
    m_id = id;
    m_parent = parent;
    m_metadata = metadata;
    m_barrier = make_shared<Barrier>(metadata->get_node_count());
}

void INetwork::BuildTopology(ns3::PointToPointHelper p2p,      //
                             vector<shared_ptr<Node>> &nodes,  //
                             vector<shared_ptr<Switch>> &switchs) {
    __TRACE_LOG__
    switch (m_metadata->get_topology_type()) {
        case TopologyType::FULLCONNECTED:
            Topology::FullConnected(p2p, m_metadata, nodes, switchs);
            break;
        case TopologyType::FATTREE:
            Topology::FatTree(p2p, m_metadata, nodes, switchs);
            break;
        case TopologyType::LINEAR:
            Topology::Linear(p2p, m_metadata, nodes, switchs);
            break;
        case TopologyType::RING:
            Topology::Ring(p2p, m_metadata, nodes, switchs);
            break;
        case TopologyType::MESH_2D:
            Topology::Mesh2D(p2p, m_metadata, nodes, switchs);
            break;
        case TopologyType::TORUS_2D:
            Topology::Torus2D(p2p, m_metadata, nodes, switchs);
            break;
        default:
            LOGE("unhandled type");
            break;
    }
}

}  // namespace adpart_sim

namespace adpart_sim {

Network::Network(Core *parent, size_t id, shared_ptr<NetworkMetadata> metadata) {
    __TRACE_LOG__
    // m_type
    m_type = metadata->get_network_type();
    switch (m_type) {
        case NetworkType::PHY:
            m_network = make_shared<Network_Phy>(parent, id, metadata);
            break;
        case NetworkType::ETHERNET:
            m_network = make_shared<Network_Ethernet>(parent, id, metadata);
            break;
        default:
            LOGE("unhandled type");
    }
}

void Network::BarrierClear() {
    ASSERT(m_network);
    m_network->get_barrier()->Clear();
}

void Network::BarrierWait(std::function<void()> callback) {
    ASSERT(m_network);
    m_network->get_barrier()->Wait(callback);
}

void Network::BuildTopology(unordered_map<size_t, shared_ptr<Node>> &nodes,
                            unordered_map<size_t, shared_ptr<Switch>> &switchs) {
    __TRACE_LOG__
    ASSERT(m_network);
    vector<shared_ptr<Node>> sub_nodes;
    vector<shared_ptr<Switch>> sub_switchs;
    size_t node_index = 0;
    size_t switch_index = 0;
    size_t repeats = get_metadata()->get_repeat_count();
    size_t subnode_count = get_metadata()->get_node_count();
    size_t subswitch_count = get_metadata()->get_switch_count();
    LOGE_IF(nodes.size() < subnode_count * repeats, "the given number of nodes is too small");
    LOGE_IF(switchs.size() < subswitch_count * repeats, "the given number of switchs is too small");
    for (size_t i = 0; i < repeats; i++) {
        sub_nodes.clear();
        sub_switchs.clear();
        node_index = i * subnode_count;
        switch_index = i * subswitch_count;
        for (size_t j = 0; j < subnode_count; j++) sub_nodes.push_back(nodes[node_index + j]);
        for (size_t j = 0; j < subswitch_count; j++) sub_switchs.push_back(switchs[switch_index + j]);
        m_network->BuildTopology(sub_nodes, sub_switchs);
    }
}

}  // namespace adpart_sim