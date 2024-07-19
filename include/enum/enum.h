#pragma once
#include "enum/accelerator.h"
#include "enum/algorithm.h"
#include "enum/communication.h"
#include "enum/compute.h"
#include "enum/network.h"
#include "enum/strategy.h"
#include "enum/task.h"
#include "enum/topology.h"
#include "utils/configuration.h"

namespace adpart_sim {

template <typename T>
T GetType(std::string type, std::unordered_map<std::string, T> map, T default_value);

template <typename T>
std::string GetType(T type, std::unordered_map<std::string, T> map);

}  // namespace adpart_sim
