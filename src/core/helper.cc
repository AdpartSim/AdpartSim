#include "core/helper.h"
#include "ns3/callback.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

static size_t g_device_id = 0;

Device::Device(size_t network_id,                    //
               shared_ptr<INodeHelper> src_node,     //
               shared_ptr<INodeHelper> dst_node,     //
               ns3::Ptr<ns3::NetDevice> src_device,  //
               ns3::Ptr<ns3::NetDevice> dst_device) {
    __TRACE_LOG__
    m_src_node = src_node;
    m_dst_node = dst_node;
    m_src_device = src_device;
    m_dst_device = dst_device;
    m_network_id = network_id;
    m_device_id = g_device_id++;
    m_src_device->TraceConnectWithoutContext("PhyTxEnd", ns3::MakeCallback(&Device::SendPacketComplete, this));
    m_src_device->TraceConnectWithoutContext("PhyRxEnd", ns3::MakeCallback(&Device::RecvPacketComplete, this));
}

void Device::RecvPacketComplete(ns3::Ptr<const ns3::Packet> packet) {
    __TRACE_LOG__
    m_total_recv_size_byte += packet->GetSize();
    if (m_recv_callback != nullptr) {
        m_recv_callback(packet, m_dst_node->get_node_id());
    }
}

void Device::SendPacketComplete(ns3::Ptr<const ns3::Packet> packet) {
    __TRACE_LOG__
    m_total_send_size_byte += packet->GetSize();
    if (m_send_callback != nullptr) {
        m_send_callback(packet, m_dst_node->get_node_id());
    }
}

void Device::SetSendBeginCallback(function<void(size_t to_device_id)> send_begin_callback) {
    __TRACE_LOG__
    m_send_begin_callback = send_begin_callback;
}

void Device::SetSendCallback(function<void(ns3::Ptr<ns3::Packet const> packet, size_t to_node_id)> send_callback) {
    __TRACE_LOG__
    m_send_callback = send_callback;
}

void Device::SetRecvCallback(function<void(ns3::Ptr<ns3::Packet const> packet, size_t from_node_id)> recv_callback) {
    __TRACE_LOG__
    m_recv_callback = recv_callback;
}

bool Device::Send(size_t size_byte) {
    __TRACE_LOG__
    size_t now_ns = ns3::Simulator::Now().GetNanoSeconds();
    ns3::Ptr<ns3::Packet> packet = ns3::Create<ns3::Packet>(size_byte);
    g_configuration->traffic_file << now_ns << ","                     //
                                  << GetTimeStr(now_ns) << ","         //
                                  << m_network_id << ","               //
                                  << m_src_node->get_node_id() << ","  //
                                  << m_dst_node->get_node_id() << ","  //
                                  << packet->GetSize() << ","          //
                                  << GetSizeStr(packet->GetSize()) << "\n";
    if (m_send_begin_callback != nullptr) {
        m_send_begin_callback(m_dst_node->get_node_id());
    }
    m_heatmap_data[m_dst_node->get_node_id()] += packet->GetSize();
    return m_src_device->Send(packet, m_dst_device->GetAddress(), 0x0800);
}

}  // namespace adpart_sim

namespace adpart_sim {

INodeHelper::INodeHelper(Core *parent, size_t node_id) {
    __TRACE_LOG__
    m_parent = parent;
    m_node_id = node_id;
    m_ns3_node = ns3::CreateObject<ns3::Node>();
}

}  // namespace adpart_sim
