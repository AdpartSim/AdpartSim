#include "metadata/communicator.h"

using namespace std;

namespace adpart_sim {

// m_parent
NodeMetadata *CommunicatorMetadata::get_parent() { return m_parent; }

// m_buffer_size_mb
double CommunicatorMetadata::get_buffer_size_mb() { return m_buffer_size_mb; }

string CommunicatorMetadata::get_buffer_size_str() { return GetSizeStr(m_buffer_size_mb); }

// m_algorithm_type
AlgorithmType CommunicatorMetadata::get_algorithm_type() { return m_algorithm_type; }

string CommunicatorMetadata::get_algorithm_type_str() { return GetAlgorithmType(m_algorithm_type); }

// m_recv_timeout_s
double CommunicatorMetadata::get_recv_timeout_s() { return m_recv_timeout_s; }

string CommunicatorMetadata::get_recv_timeout_str() { return GetTimeStr(m_recv_timeout_s); }

}  // namespace adpart_sim