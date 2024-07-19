#pragma once
#include "enum/enum.h"
#include "utils/configuration.h"

namespace adpart_sim {

class ComputeTask {
   public:
    explicit ComputeTask();
    explicit ComputeTask(size_t runtime_ns);
    explicit ComputeTask(ComputeDataType data_type, ComputeOpsType ops_type, size_t size_byte);

   public:
    // m_size_byte
    size_t get_size_byte();
    std::string get_size_str();
    // m_runtime_ns
    size_t get_runtime_ns();
    std::string get_runtime_str();
    // m_ops_type
    ComputeOpsType get_ops_type();
    std::string get_ops_type_str();
    // m_data_type
    ComputeDataType get_data_type();
    std::string get_data_type_str();

   private:
    size_t m_size_byte = 0;
    size_t m_runtime_ns = 0;
    ComputeOpsType m_ops_type = ComputeOpsType::INVALID;
    ComputeDataType m_data_type = ComputeDataType::INVALID;
};

}  // namespace adpart_sim
