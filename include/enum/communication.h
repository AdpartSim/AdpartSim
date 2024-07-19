#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class CommunicationType {
    INVALID,
    P2P_SEND,
    P2P_RECV,
    BARRIER,
    REDUCE,
    GATHER,
    SCATTER,
    BROADCAST,
    ALL_TO_ALL,
    ALL_GATHER,
    ALL_REDUCE,
    REDUCE_SCATTER,
    RESERVED,
};

CommunicationType GetCommunicationType(std::string type);

std::string GetCommunicationType(CommunicationType type);

bool IsAllToAll(CommunicationType type);

bool IsAllToOne(CommunicationType type);

bool IsOneToAll(CommunicationType type);

bool IsOneToOne(CommunicationType type);

}  // namespace adpart_sim
