#include "network/network.h"
#include "ns3/string.h"

using namespace std;

namespace adpart_sim {

class Network_Ethernet : public INetwork {
   public:
    Network_Ethernet(Core *parent, size_t id, shared_ptr<NetworkMetadata> metadata) : INetwork(parent, id, metadata) {
        __TRACE_LOG__
        //
    }

    void BuildTopology(vector<shared_ptr<Node>> &nodes, vector<shared_ptr<Switch>> &switchs) override {
        __TRACE_LOG__
        //
    }
};

}  // namespace adpart_sim