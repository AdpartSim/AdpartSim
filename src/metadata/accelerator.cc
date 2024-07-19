#include "metadata/accelerator.h"

using namespace std;

namespace adpart_sim {

AcceleratorMetadata::AcceleratorMetadata(NodeMetadata *parent, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_type
    m_type = GetAcceleratorType(Json::GetStr(json, "Type"));
    // m_latency_ns
    Json::Parse(m_latency_ns, json, "Latency_ns");
    // m_clockfreq_ghz
    Json::Parse(m_clockfreq_ghz, json, "ClockFreq_GHz");
    // m_performance_tflops
    Json::Parse(m_performance_tflops, json, "Performance_TFLOPS");
}

}  // namespace adpart_sim