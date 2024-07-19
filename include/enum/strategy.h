#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class StrategyType {
    INVALID,
    CHAKRA,
    TESTCASE,
    RESERVED,
};

StrategyType GetStrategyType(std::string type);

std::string GetStrategyType(StrategyType type);

}  // namespace adpart_sim
