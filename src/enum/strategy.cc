#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, StrategyType> const StrategyTypeMap = {
    {"INVALID", StrategyType::INVALID},
    {"CHAKRA", StrategyType::CHAKRA},
    {"TESTCASE", StrategyType::TESTCASE},
    {"RESERVED", StrategyType::RESERVED},
};

StrategyType GetStrategyType(string type) { return GetType(type, StrategyTypeMap, StrategyType::INVALID); }

string GetStrategyType(StrategyType type) { return GetType(type, StrategyTypeMap); }

}  // namespace adpart_sim
