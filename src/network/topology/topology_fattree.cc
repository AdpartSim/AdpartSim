#include "network/topology.h"

using namespace std;

namespace adpart_sim {

void Topology::FatTree(                    //
    ns3::PointToPointHelper p2p,           //
    shared_ptr<NetworkMetadata> metadata,  //
    vector<shared_ptr<Node>> &nodes,       //
    vector<shared_ptr<Switch>> &switchs) {
    __TRACE_LOG__
    bool check_result = nodes.size() > 0 && switchs.size() > 0;
    LOGE_IF(!(check_result), "The switch topology requires nodes and switchs");
    if (check_result) {
        for (size_t i = 0; i < nodes.size(); i++) {
            for (size_t j = 0; j < switchs.size(); j++) {
                Link(p2p, metadata, nodes[i], switchs[j]);
            }
        }
    }
}

}  // namespace adpart_sim
