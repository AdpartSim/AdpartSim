#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, ComputeDataType> const ComputeDataTypeMap = {
    {"INVALID", ComputeDataType::INVALID},    //
    {"FP32", ComputeDataType::FP32},          //
    {"FP16", ComputeDataType::FP16},          //
    {"BF16", ComputeDataType::BF16},          //
    {"INT8", ComputeDataType::INT8},          //
    {"INT16", ComputeDataType::INT16},        //
    {"RESERVED", ComputeDataType::RESERVED},  //
};

ComputeDataType GetComputeDataType(string type) { return GetType(type, ComputeDataTypeMap, ComputeDataType::INVALID); }

string GetComputeDataType(ComputeDataType type) { return GetType(type, ComputeDataTypeMap); }

}  // namespace adpart_sim

namespace adpart_sim {

unordered_map<string, ComputeOpsType> const ComputeOpsTypeMap = {
    {"INVALID", ComputeOpsType::INVALID},
    {"ADD", ComputeOpsType::ADD},
    {"GEMM", ComputeOpsType::GEMM},
    {"RESERVED", ComputeOpsType::RESERVED},
};

ComputeOpsType GetComputeOpsType(string type) { return GetType(type, ComputeOpsTypeMap, ComputeOpsType::INVALID); }

string GetComputeOpsType(ComputeOpsType type) { return GetType(type, ComputeOpsTypeMap); }

}  // namespace adpart_sim
