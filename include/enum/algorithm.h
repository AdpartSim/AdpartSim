#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class AlgorithmType {
    INVALID,
    DIRECT,
    RESERVED,
};

AlgorithmType GetAlgorithmType(std::string type);

std::string GetAlgorithmType(AlgorithmType type);

}  // namespace adpart_sim
