#include "task/task.h"

using namespace std;

namespace adpart_sim {

// m_size_byte
size_t ComputeTask::get_size_byte() { return m_size_byte; }

string ComputeTask::get_size_str() { return GetSizeStr(m_size_byte); }

// m_runtime_ns
size_t ComputeTask::get_runtime_ns() { return m_runtime_ns; }

string ComputeTask::get_runtime_str() { return GetTimeStr(m_runtime_ns); }

// m_ops_type
ComputeOpsType ComputeTask::get_ops_type() { return m_ops_type; }

string ComputeTask::get_ops_type_str() { return GetComputeOpsType(m_ops_type); }

// m_data_type
ComputeDataType ComputeTask::get_data_type() { return m_data_type; }

string ComputeTask::get_data_type_str() { return GetComputeDataType(m_data_type); }

}  // namespace adpart_sim
