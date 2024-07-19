#include "network/topology.h"

using namespace std;

namespace adpart_sim {

void Topology::Torus2D(                    //
    ns3::PointToPointHelper p2p,           //
    shared_ptr<NetworkMetadata> metadata,  //
    vector<shared_ptr<Node>> &nodes,       //
    vector<shared_ptr<Switch>> &switchs) {
    __TRACE_LOG__
    bool node_link = nodes.size() > 0 && switchs.size() <= 0;
    bool switch_link = nodes.size() <= 0 && switchs.size() > 0;
    size_t total_num = node_link ? nodes.size() : (switch_link ? switchs.size() : 0);
    LOGE_IF(!(node_link || switch_link), "The mesh2d topology allows only one device type");
    if ((node_link || switch_link) && total_num > 0) {
        size_t width = 0;
        size_t height = 0;
        if (metadata->get_topology_attrs().size() > 1) {
            width = metadata->get_topology_attrs()[0];
            height = metadata->get_topology_attrs()[1];
        } else if (metadata->get_topology_attrs().size() > 0) {
            width = metadata->get_topology_attrs()[0];
            height = static_cast<size_t>(floor(total_num / width));
        } else {
            width = static_cast<size_t>(sqrt(total_num));
            height = width;
        }
        bool result = width * height == total_num;
        LOGW_IF(!result, "Unable to infer the appropriate dimension based on the number of nodes");
        if (result) {
            for (size_t i = 0; i < width; i++) {
                for (size_t j = 0; j < height; j++) {
                    size_t src = i * width + j;
                    if (i + 1 < width)
                        Link(p2p, metadata, nodes, switchs, node_link, switch_link, src, (i + 1) * width + j);
                    else
                        Link(p2p, metadata, nodes, switchs, node_link, switch_link, src, j);
                    if (j + 1 < height)
                        Link(p2p, metadata, nodes, switchs, node_link, switch_link, src, i * width + (j + 1));
                    else
                        Link(p2p, metadata, nodes, switchs, node_link, switch_link, src, i * width);
                }
            }
        }
    }
}

}  // namespace adpart_sim
