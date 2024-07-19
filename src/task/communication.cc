#include "task/task.h"

using namespace std;

namespace adpart_sim {

CommunicationTask::CommunicationTask() {}

CommunicationTask::CommunicationTask(      //
    CommunicationType communication_type,  //
    size_t size_byte                       //
) {
    __TRACE_LOG__
    // All to All
    LOGE_IF(!IsAllToAll(communication_type), "constructs that call this method are not allowed");
    m_communication_type = communication_type;
    m_size_byte = size_byte;
}

CommunicationTask::CommunicationTask(      //
    CommunicationType communication_type,  //
    size_t size_byte,                      //
    size_t root                            //
) {
    __TRACE_LOG__
    // One to All or All to One
    bool check_result = IsAllToOne(communication_type) || IsOneToAll(communication_type);
    LOGE_IF(!check_result, "constructs that call this method are not allowed");
    m_communication_type = communication_type;
    m_size_byte = size_byte;
    m_root = root;
}

CommunicationTask::CommunicationTask(      //
    CommunicationType communication_type,  //
    size_t size_byte,                      //
    size_t src,                            //
    size_t dst                             //
) {
    __TRACE_LOG__
    // One to One
    LOGE_IF(!IsOneToOne(communication_type), "constructs that call this method are not allowed");
    m_communication_type = communication_type;
    m_size_byte = size_byte;
    m_src = src;
    m_dst = dst;
}

CommunicationTask::CommunicationTask(      //
    CommunicationType communication_type,  //
    size_t size_byte,                      //
    size_t src,                            //
    size_t root,                           //
    size_t dst                             //
) {
    __TRACE_LOG__
    // Common
    if (IsOneToOne(communication_type)) {
        m_src = src;
        m_dst = dst;
        m_root = _MAX_SIZE_T_;
    } else if (IsOneToAll(communication_type) || IsAllToOne(communication_type)) {
        m_src = _MAX_SIZE_T_;
        m_dst = _MAX_SIZE_T_;
        m_root = root;
    } else if (IsAllToAll(communication_type)) {
        m_src = _MAX_SIZE_T_;
        m_dst = _MAX_SIZE_T_;
        m_root = _MAX_SIZE_T_;
    } else {
        LOGE("constructs that call this method are not allowed");
    }
    m_communication_type = communication_type;
    m_size_byte = size_byte;
}

}  // namespace adpart_sim
