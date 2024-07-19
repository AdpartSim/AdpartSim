#pragma once
#include "ns3/address.h"
#include "ns3/net-device.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Core;
class INodeHelper;

class Device {
   public:
    Device(size_t network_id,                        //
           std::shared_ptr<INodeHelper> src_node,    //
           std::shared_ptr<INodeHelper> dst_node,    //
           ns3::Ptr<ns3::NetDevice> ns3_src_device,  //
           ns3::Ptr<ns3::NetDevice> ns3_dst_device);

   public:
    void SetSendBeginCallback(std::function<void(size_t to_device_id)> send_begin_callback);
    void SetSendCallback(std::function<void(ns3::Ptr<ns3::Packet const> packet, size_t to_node_id)> send_callback);
    void SetRecvCallback(std::function<void(ns3::Ptr<ns3::Packet const> packet, size_t from_node_id)> recv_callback);
    void RecvPacketComplete(ns3::Ptr<const ns3::Packet> packet);
    void SendPacketComplete(ns3::Ptr<const ns3::Packet> packet);
    bool Send(size_t size_byte);

   public:
    // m_device_id
    size_t get_device_id();
    // m_network_id
    size_t get_network_id();
    // m_src_device
    std::shared_ptr<INodeHelper> get_src_node();
    // m_dst_node
    std::shared_ptr<INodeHelper> get_dst_node();
    // m_src_device
    ns3::Ptr<ns3::NetDevice> get_src_device();
    // m_dst_device
    ns3::Ptr<ns3::NetDevice> get_dst_device();
    // m_total_send_size_byte
    size_t get_total_send_size_byte();
    std::string get_total_send_size_str();
    // m_total_recv_size_byte
    size_t get_total_recv_size_byte();
    std::string get_total_recv_size_str();
    // m_heatmap_data
    std::unordered_map<size_t, size_t> get_heatmap_data();

   private:
    size_t m_device_id = 0;
    size_t m_network_id = 0;
    std::shared_ptr<INodeHelper> m_src_node = nullptr;
    std::shared_ptr<INodeHelper> m_dst_node = nullptr;
    ns3::Ptr<ns3::NetDevice> m_src_device = nullptr;
    ns3::Ptr<ns3::NetDevice> m_dst_device = nullptr;

   private:
    size_t m_total_send_size_byte = 0;
    size_t m_total_recv_size_byte = 0;
    std::unordered_map<size_t, size_t> m_heatmap_data = {};
    std::function<void(size_t to_device_id)> m_send_begin_callback = nullptr;
    std::function<void(ns3::Ptr<ns3::Packet const> packet, size_t to_node_id)> m_send_callback = nullptr;
    std::function<void(ns3::Ptr<ns3::Packet const> packet, size_t from_node_id)> m_recv_callback = nullptr;
};

class INodeHelper {
   public:
    explicit INodeHelper(Core *parent, size_t node_id);

   public:
    // m_parent
    Core *get_parent();
    // m_node_id
    size_t get_node_id();
    // m_ns3_node
    ns3::Ptr<ns3::Node> get_ns3_node();
    // m_devices
    size_t get_network_dims();
    std::vector<std::shared_ptr<Device>> &get_devices(size_t network_id);
    void add_device(size_t network_id, std::shared_ptr<Device> device, size_t delay_ns);

   protected:
    Core *m_parent = nullptr;
    size_t m_node_id = _MAX_SIZE_T_;
    size_t m_network_id = _MAX_SIZE_T_;
    ns3::Ptr<ns3::Node> m_ns3_node = nullptr;
    std::unordered_map<size_t, std::vector<std::shared_ptr<Device>>> m_devices;
};

}  // namespace adpart_sim
