#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class TopologyType {
    INVALID,
    FULLCONNECTED,
    FATTREE,
    LINEAR,
    RING,
    MESH_2D,
    TORUS_2D,
    RESERVED,
};

TopologyType GetTopologyType(std::string type);

std::string GetTopologyType(TopologyType type);

}  // namespace adpart_sim
