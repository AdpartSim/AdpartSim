#pragma once
#include "enum/enum.h"
#include "utils/configuration.h"

namespace adpart_sim {

class CommunicationTask {
   public:
    explicit CommunicationTask();
    explicit CommunicationTask(                //
        CommunicationType communication_type,  //
        size_t size_byte                       //
    );
    explicit CommunicationTask(                //
        CommunicationType communication_type,  //
        size_t size_byte,                      //
        size_t root                            //
    );
    explicit CommunicationTask(                //
        CommunicationType communication_type,  //
        size_t size_byte,                      //
        size_t src,                            //
        size_t dst                             //
    );
    explicit CommunicationTask(                //
        CommunicationType communication_type,  //
        size_t size_byte,                      //
        size_t root,                           //
        size_t src,                            //
        size_t dst                             //
    );

   public:
    // m_communication_type
    CommunicationType get_communication_type();
    std::string get_communication_type_str();
    // m_priority
    size_t get_priority();
    // m_size_byte
    size_t get_size_byte();
    std::string get_size_str();
    // m_root
    size_t get_root();
    // m_src
    size_t get_src();
    // m_dst
    size_t get_dst();
    // m_tag
    size_t get_tag();

   private:
    CommunicationType m_communication_type = CommunicationType::INVALID;
    size_t m_size_byte = 0;
    size_t m_root = _MAX_SIZE_T_;
    size_t m_src = _MAX_SIZE_T_;
    size_t m_dst = _MAX_SIZE_T_;
};

}  // namespace adpart_sim
