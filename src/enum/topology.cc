#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, TopologyType> const TopologyTypeMap = {
    {"INVALID", TopologyType::INVALID},              //
    {"FULLCONNECTED", TopologyType::FULLCONNECTED},  //
    {"FATTREE", TopologyType::FATTREE},              //
    {"LINEAR", TopologyType::LINEAR},                //
    {"RING", TopologyType::RING},                    //
    {"MESH_2D", TopologyType::MESH_2D},              //
    {"TORUS_2D", TopologyType::TORUS_2D},            //
    {"RESERVED", TopologyType::RESERVED},            //
};

TopologyType GetTopologyType(string type) { return GetType(type, TopologyTypeMap, TopologyType::INVALID); }

string GetTopologyType(TopologyType type) { return GetType(type, TopologyTypeMap); }

}  // namespace adpart_sim
