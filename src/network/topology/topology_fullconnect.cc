#include "network/topology.h"

using namespace std;

namespace adpart_sim {

void Topology::FullConnected(              //
    ns3::PointToPointHelper p2p,           //
    shared_ptr<NetworkMetadata> metadata,  //
    vector<shared_ptr<Node>> &nodes,       //
    vector<shared_ptr<Switch>> &switchs) {
    __TRACE_LOG__
    bool node_link = nodes.size() > 0 && switchs.size() <= 0;
    bool switch_link = nodes.size() <= 0 && switchs.size() > 0;
    size_t total_num = node_link ? nodes.size() : (switch_link ? switchs.size() : 0);
    LOGE_IF(!(node_link || switch_link), "The fullconnected topology allows only one device type");
    for (size_t i = 0; i < total_num; i++) {
        for (size_t j = i + 1; j < total_num; j++) {
            Link(p2p, metadata, nodes, switchs, node_link, switch_link, i, j);
        }
    }
}

}  // namespace adpart_sim
