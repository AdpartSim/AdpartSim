#include "network/topology.h"
#include "ns3/net-device-container.h"
#include "ns3/node-container.h"

using namespace std;

namespace adpart_sim {

void Topology::Link(                       //
    ns3::PointToPointHelper p2p,           //
    shared_ptr<NetworkMetadata> metadata,  //
    shared_ptr<INodeHelper> src,           //
    shared_ptr<INodeHelper> dst) {
    __TRACE_LOG__
    size_t network_id = metadata->get_id();
    ns3::NetDeviceContainer devices = p2p.Install(src->get_ns3_node(), dst->get_ns3_node());
    shared_ptr<Device> src_device = make_shared<Device>(network_id, src, dst, devices.Get(0), devices.Get(1));
    shared_ptr<Device> dst_device = make_shared<Device>(network_id, dst, src, devices.Get(1), devices.Get(0));
    src->add_device(network_id, src_device, metadata->get_latency_ns());
    dst->add_device(network_id, dst_device, metadata->get_latency_ns());
}

void Topology::Link(                       //
    ns3::PointToPointHelper p2p,           //
    shared_ptr<NetworkMetadata> metadata,  //
    vector<shared_ptr<Node>>& nodes,       //
    vector<shared_ptr<Switch>>& switchs,   //
    bool node_link,                        //
    bool switch_link,                      //
    size_t src,                            //
    size_t dst) {
    __TRACE_LOG__
    if (node_link)
        Link(p2p, metadata, nodes[src], nodes[dst]);
    else if (switch_link)
        Link(p2p, metadata, switchs[src], switchs[src]);
    else
        LOGW("Undetermined network topology connection");
}

}  // namespace adpart_sim
