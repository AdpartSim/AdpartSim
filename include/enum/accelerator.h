#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class AcceleratorType {
    INVALID,
    DIRECT,
    RESERVED,
};

AcceleratorType GetAcceleratorType(std::string type);

std::string GetAcceleratorType(AcceleratorType type);

}  // namespace adpart_sim
