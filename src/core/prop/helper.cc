
#include "core/helper.h"
#include "ns3/timer.h"

using namespace std;

namespace adpart_sim {

// m_device_id
size_t Device::get_device_id() { return m_device_id; }

// m_network_id
size_t Device::get_network_id() { return m_network_id; }

// m_src_node
std::shared_ptr<INodeHelper> Device::get_src_node() { return m_src_node; }

// m_dst_node
std::shared_ptr<INodeHelper> Device::get_dst_node() { return m_dst_node; }

// m_src_device
ns3::Ptr<ns3::NetDevice> Device::get_src_device() { return m_src_device; }

// m_dst_device
ns3::Ptr<ns3::NetDevice> Device::get_dst_device() { return m_dst_device; }

// m_total_send_size_byte
size_t Device::get_total_send_size_byte() { return m_total_send_size_byte; }

std::string Device::get_total_send_size_str() { return GetSizeStr(m_total_send_size_byte); }

// m_total_recv_size_byte
size_t Device::get_total_recv_size_byte() { return m_total_recv_size_byte; }

std::string Device::get_total_recv_size_str() { return GetSizeStr(m_total_recv_size_byte); }

// m_heatmap_data
unordered_map<size_t, size_t> Device::get_heatmap_data() { return m_heatmap_data; }

}  // namespace adpart_sim

namespace adpart_sim {

// m_parent
Core* INodeHelper::get_parent() { return m_parent; }

// m_node_id
size_t INodeHelper::get_node_id() { return m_node_id; }

// m_ns3_node
ns3::Ptr<ns3::Node> INodeHelper::get_ns3_node() { return m_ns3_node; }

// m_devices
size_t INodeHelper::get_network_dims() { return m_devices.size(); }

vector<shared_ptr<Device>>& INodeHelper::get_devices(size_t network_id) {
    LOGE_IF(m_devices.count(network_id) <= 0, "out of index");
    return m_devices[network_id];
}

void INodeHelper::add_device(size_t network_id, std::shared_ptr<Device> device, size_t delay_ns) {
    device->get_src_device()->SetAttribute("InterframeGap", ns3::TimeValue(ns3::NanoSeconds(delay_ns)));
    device->get_dst_device()->SetAttribute("InterframeGap", ns3::TimeValue(ns3::NanoSeconds(delay_ns)));
    m_devices[network_id].push_back(device);
}

}  // namespace adpart_sim