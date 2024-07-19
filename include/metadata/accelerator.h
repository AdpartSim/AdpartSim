#pragma once
#include "enum/enum.h"
#include "utils/configuration.h"

namespace adpart_sim {

class NodeMetadata;

class AcceleratorMetadata {
   public:
    explicit AcceleratorMetadata(NodeMetadata *parent, JsonCpp const &json);

   public:
    // m_parent
    NodeMetadata *get_parent();
    // m_type
    AcceleratorType get_type();
    std::string get_type_str();
    // m_latency_ns
    size_t get_latency_ns();
    std::string get_latency_str();
    // m_clockfreq_ghz
    double get_clockfreq_ghz();
    std::string get_clockfreq_str();
    // m_performance_tflops
    double get_performance_tflops();
    std::string get_performance_str();

   private:
    NodeMetadata *m_parent = nullptr;
    AcceleratorType m_type = AcceleratorType::INVALID;
    size_t m_latency_ns = 0;
    double m_clockfreq_ghz = 0;
    double m_performance_tflops = 0;
};

}  // namespace adpart_sim
