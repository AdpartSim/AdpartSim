#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, NetworkType> const NetworkTypeMap = {
    {"INVALID", NetworkType::INVALID},
    {"PHY", NetworkType::PHY},
    {"ETHERNET", NetworkType::ETHERNET},
    {"RESERVED", NetworkType::RESERVED},
};

NetworkType GetNetworkType(string type) { return GetType(type, NetworkTypeMap, NetworkType::INVALID); }

string GetNetworkType(NetworkType type) { return GetType(type, NetworkTypeMap); }

}  // namespace adpart_sim
