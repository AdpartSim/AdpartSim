#pragma once
#include "core/helper.h"
#include "metadata/network.h"
#include "node/node.h"
#include "ns3/point-to-point-helper.h"
#include "switch/switch.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Topology {
   public:
    static void Link(ns3::PointToPointHelper p2p,                //
                     std::shared_ptr<NetworkMetadata> metadata,  //
                     std::shared_ptr<INodeHelper> src,           //
                     std::shared_ptr<INodeHelper> dst);

    static void Link(ns3::PointToPointHelper p2p,                    //
                     std::shared_ptr<NetworkMetadata> metadata,      //
                     std::vector<std::shared_ptr<Node>> &nodes,      //
                     std::vector<std::shared_ptr<Switch>> &switchs,  //
                     bool node_link,                                 //
                     bool switch_link,                               //
                     size_t src,                                     //
                     size_t dst);

    static void FullConnected(ns3::PointToPointHelper p2p,                //
                              std::shared_ptr<NetworkMetadata> metadata,  //
                              std::vector<std::shared_ptr<Node>> &nodes,  //
                              std::vector<std::shared_ptr<Switch>> &switchs);

    static void FatTree(ns3::PointToPointHelper p2p,                //
                        std::shared_ptr<NetworkMetadata> metadata,  //
                        std::vector<std::shared_ptr<Node>> &nodes,  //
                        std::vector<std::shared_ptr<Switch>> &switchs);

    static void Linear(ns3::PointToPointHelper p2p,                //
                       std::shared_ptr<NetworkMetadata> metadata,  //
                       std::vector<std::shared_ptr<Node>> &nodes,  //
                       std::vector<std::shared_ptr<Switch>> &switchs);

    static void Ring(ns3::PointToPointHelper p2p,                //
                     std::shared_ptr<NetworkMetadata> metadata,  //
                     std::vector<std::shared_ptr<Node>> &nodes,  //
                     std::vector<std::shared_ptr<Switch>> &switchs);

    static void Mesh2D(ns3::PointToPointHelper p2p,                //
                       std::shared_ptr<NetworkMetadata> metadata,  //
                       std::vector<std::shared_ptr<Node>> &nodes,  //
                       std::vector<std::shared_ptr<Switch>> &switchs);

    static void Torus2D(ns3::PointToPointHelper p2p,                //
                        std::shared_ptr<NetworkMetadata> metadata,  //
                        std::vector<std::shared_ptr<Node>> &nodes,  //
                        std::vector<std::shared_ptr<Switch>> &switchs);
};

}  // namespace adpart_sim