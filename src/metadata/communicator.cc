#include "metadata/communicator.h"

using namespace std;

namespace adpart_sim {

CommunicatorMetadata::CommunicatorMetadata(NodeMetadata *parent, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_buffer_size_mb
    Json::Parse(m_buffer_size_mb, json, "BufferSize_MB");
    LOGE_IF(m_buffer_size_mb > 512, "The size of the buffer cannot exceed 512 MB");
    // m_algorithm_type
    m_algorithm_type = GetAlgorithmType(Json::GetStr(json, "Algorithm"));
    // m_recv_timeout_s
    Json::Parse(m_recv_timeout_s, json, "ReceiveTimeout_s");
}

}  // namespace adpart_sim