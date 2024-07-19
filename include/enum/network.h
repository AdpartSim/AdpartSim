#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class NetworkType {
    INVALID,
    PHY,
    ETHERNET,
    RESERVED,
};

NetworkType GetNetworkType(std::string type);

std::string GetNetworkType(NetworkType type);

}  // namespace adpart_sim
