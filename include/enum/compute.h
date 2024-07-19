#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class ComputeDataType {
    INVALID,
    FP32,
    FP16,
    BF16,
    INT8,
    INT16,
    RESERVED,
};

ComputeDataType GetComputeDataType(std::string type);

std::string GetComputeDataType(ComputeDataType type);

}  // namespace adpart_sim

namespace adpart_sim {

enum class ComputeOpsType {
    INVALID,
    ADD,
    GEMM,
    RESERVED,
};

ComputeOpsType GetComputeOpsType(std::string type);

std::string GetComputeOpsType(ComputeOpsType type);

}  // namespace adpart_sim
