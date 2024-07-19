#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, AlgorithmType> const AlgorithmTypeMap = {
    {"INVALID", AlgorithmType::INVALID},
    {"DIRECT", AlgorithmType::DIRECT},
    {"RESERVED", AlgorithmType::RESERVED},
};

AlgorithmType GetAlgorithmType(string type) { return GetType(type, AlgorithmTypeMap, AlgorithmType::INVALID); }

string GetAlgorithmType(AlgorithmType type) { return GetType(type, AlgorithmTypeMap); }

}  // namespace adpart_sim
