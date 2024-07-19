#include "network/network.h"
#include "ns3/string.h"

using namespace std;

namespace adpart_sim {

class Network_Phy : public INetwork {
   public:
    Network_Phy(Core *parent, size_t id, shared_ptr<NetworkMetadata> metadata) : INetwork(parent, id, metadata) {
        __TRACE_LOG__
        LOGE_IF(metadata->get_switch_count() > 0, "The phy network does not allow switches");
    }

    void BuildTopology(vector<shared_ptr<Node>> &nodes, vector<shared_ptr<Switch>> &switchs) override {
        __TRACE_LOG__
        ns3::PointToPointHelper p2p;
        std::string bandwidth = std::to_string(get_metadata()->get_bandwidth_gbps()) + "Gbps";
        std::string latency = std::to_string(get_metadata()->get_latency_ns()) + "ns";
        p2p.SetDeviceAttribute("DataRate", ns3::StringValue(bandwidth));
        p2p.SetChannelAttribute("Delay", ns3::StringValue(latency));
        INetwork::BuildTopology(p2p, nodes, switchs);
    }
};

}  // namespace adpart_sim