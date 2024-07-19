#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, AcceleratorType> const AcceleratorTypeMap = {
    {"INVALID", AcceleratorType::INVALID},
    {"DIRECT", AcceleratorType::DIRECT},
    {"RESERVED", AcceleratorType::RESERVED},
};

AcceleratorType GetAcceleratorType(string type) { return GetType(type, AcceleratorTypeMap, AcceleratorType::INVALID); }

string GetAcceleratorType(AcceleratorType type) { return GetType(type, AcceleratorTypeMap); }

}  // namespace adpart_sim
