#include "task/task.h"

using namespace std;

namespace adpart_sim {

ComputeTask::ComputeTask() {}

ComputeTask::ComputeTask(size_t runtime_ns) {
    __TRACE_LOG__
    m_runtime_ns = runtime_ns;
}

ComputeTask::ComputeTask(ComputeDataType data_type, ComputeOpsType ops_type, size_t size_byte) {
    __TRACE_LOG__
    m_data_type = data_type;
    m_ops_type = ops_type;
    m_size_byte = size_byte;
}

}  // namespace adpart_sim
