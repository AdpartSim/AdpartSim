#pragma once
#include <map>
#include <string>

namespace adpart_sim {

std::string GetBandwidthStr(double bandwidth_gbps);

std::string GetTimeStr(size_t time_ns);

std::string GetClockFreqStr(double clockfreq_ghz);

std::string GetPerformanceStr(double performance_tflops);

std::string GetSizeStr(double size_byte);

}  // namespace adpart_sim