#include "node/node.h"

using namespace std;

namespace adpart_sim {

Node::Node(Core *parent, size_t node_id, shared_ptr<NodeMetadata> metadata) : INodeHelper(parent, node_id) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_application
    m_application = ns3::CreateObject<Application>(this, metadata);
    m_application->SetStopTime(ns3::Years(1));
    m_ns3_node->AddApplication(m_application);
}

size_t Node::GetTraffic(size_t node_id) {
    size_t traffic = 0;
    for (auto &network_it : m_devices) {
        for (auto &device_it : network_it.second) {
            unordered_map<size_t, size_t> heatmap_data = device_it->get_heatmap_data();
            traffic += heatmap_data.count(node_id) > 0 ? heatmap_data[node_id] : 0;
        }
    }
    return traffic;
}

size_t Node::GetTotalSendSizeByte() {
    size_t total_send_size_byte = 0;
    for (auto &network_it : m_devices) {
        for (auto &device_it : network_it.second) {
            total_send_size_byte += device_it->get_total_send_size_byte();
        }
    }
    return total_send_size_byte;
}

string Node::GetTotalSendSizeStr() { return GetSizeStr(GetTotalSendSizeByte()); }

size_t Node::GetTotalRecvSizeByte() {
    size_t total_recv_size_byte = 0;
    for (auto &network_it : m_devices) {
        for (auto &device_it : network_it.second) {
            total_recv_size_byte += device_it->get_total_recv_size_byte();
        }
    }
    return total_recv_size_byte;
}

string Node::GetTotalRecvSizeStr() { return GetSizeStr(GetTotalRecvSizeByte()); }

bool Node::CheckResult() {
    __TRACE_LOG__
    ASSERT(m_application);
    size_t total_send_size_byte = GetTotalSendSizeByte();
    size_t total_recv_size_byte = GetTotalRecvSizeByte();
    return m_application->CheckResult(total_send_size_byte, total_recv_size_byte);
}

void Node::InitializeNode() {
    __TRACE_LOG__
    m_application->Setup(m_devices);
}

void Node::SetTotalEpoch(size_t tota_epoch) {
    ASSERT(m_application);
    m_application->SetTotalEpoch(tota_epoch);
}

}  // namespace adpart_sim