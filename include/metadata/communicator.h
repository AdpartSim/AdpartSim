#pragma once
#include "enum/enum.h"
#include "utils/configuration.h"

namespace adpart_sim {

class NodeMetadata;

class CommunicatorMetadata {
   public:
    explicit CommunicatorMetadata(NodeMetadata *parent, JsonCpp const &json);

   public:
    // m_parent
    NodeMetadata *get_parent();
    // m_buffer_size_mb
    double get_buffer_size_mb();
    std::string get_buffer_size_str();
    // m_algorithm_type
    AlgorithmType get_algorithm_type();
    std::string get_algorithm_type_str();
    // m_recv_timeout_s
    double get_recv_timeout_s();
    std::string get_recv_timeout_str();

   private:
    NodeMetadata *m_parent = nullptr;
    double m_buffer_size_mb = 0;
    AlgorithmType m_algorithm_type = AlgorithmType::INVALID;
    double m_recv_timeout_s = 0;
};

}  // namespace adpart_sim
