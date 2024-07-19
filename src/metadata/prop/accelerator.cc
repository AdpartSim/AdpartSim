#include "metadata/accelerator.h"

using namespace std;

namespace adpart_sim {

// m_parent
NodeMetadata *AcceleratorMetadata::get_parent() { return m_parent; }

// m_type
AcceleratorType AcceleratorMetadata::get_type() { return m_type; }

string AcceleratorMetadata::get_type_str() { return GetAcceleratorType(m_type); }

// m_latency_ns
size_t AcceleratorMetadata::get_latency_ns() { return m_latency_ns; }

string AcceleratorMetadata::get_latency_str() { return GetTimeStr(m_latency_ns); }

// m_clockfreq_ghz
double AcceleratorMetadata::get_clockfreq_ghz() { return m_clockfreq_ghz; }

string AcceleratorMetadata::get_clockfreq_str() { return GetClockFreqStr(m_clockfreq_ghz); }

// m_performance_tflops
double AcceleratorMetadata::get_performance_tflops() { return m_performance_tflops; }

string AcceleratorMetadata::get_performance_str() { return GetPerformanceStr(m_performance_tflops); }

}  // namespace adpart_sim