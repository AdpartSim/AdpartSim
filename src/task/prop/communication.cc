#include "task/task.h"

using namespace std;

namespace adpart_sim {

// m_communication_type
CommunicationType CommunicationTask::get_communication_type() { return m_communication_type; }

string CommunicationTask::get_communication_type_str() { return GetCommunicationType(m_communication_type); }

// m_size_byte
size_t CommunicationTask::get_size_byte() { return m_size_byte; }

string CommunicationTask::get_size_str() { return GetSizeStr(m_size_byte); }

// m_root
size_t CommunicationTask::get_root() { return m_root; }

// m_src
size_t CommunicationTask::get_src() { return m_src; }

// m_dst
size_t CommunicationTask::get_dst() { return m_dst; }

}  // namespace adpart_sim
