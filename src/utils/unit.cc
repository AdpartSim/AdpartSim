#include "utils/unit.h"
#include <iomanip>
#include <sstream>
#include <vector>
#include "utils/configuration.h"

using namespace std;

namespace adpart_sim {

string GetBandwidthStr(double bandwidth_gbps) {
    size_t unit_index = 2;
    ostringstream bandwidth_str;
    vector<string> const units = {" Byte/s", " KiB/s", " GiB/s", " TiB/s", " PiB/s"};
    double bandwidth = bandwidth_gbps / 8;
    while (bandwidth > 1024 && unit_index < units.size() - 1) {
        bandwidth /= 1024;
        unit_index++;
    }
    while (bandwidth < 1 && unit_index >= 0) {
        if (bandwidth == 0) break;
        bandwidth *= 1024;
        unit_index--;
    }
    bandwidth_str << fixed << setprecision(2) << bandwidth << units[unit_index];
    return bandwidth_str.str();
}

string GetTimeStr(size_t time_ns) {
    double time = time_ns;
    size_t unit_index = 0;
    ostringstream latency_str;
    vector<string> const units = {" ns", " us", " ms", " s"};
    while (time > 1000 && unit_index < units.size() - 1) {
        time /= 1000;
        unit_index++;
    }
    latency_str << fixed << setprecision(2) << time << units[unit_index];
    return latency_str.str();
}

string GetClockFreqStr(double clockfreq_ghz) {
    size_t unit_index = 3;
    ostringstream clockfreq_str;
    vector<string> const units = {" Hz", " kHz", " MHz", " GHz", " THz"};
    while (clockfreq_ghz > 1000 && unit_index < units.size() - 1) {
        clockfreq_ghz /= 1000;
        unit_index++;
    }
    while (clockfreq_ghz < 1 && unit_index >= 0) {
        if (clockfreq_ghz == 0) break;
        clockfreq_ghz *= 1000;
        unit_index--;
    }
    clockfreq_str << fixed << setprecision(2) << clockfreq_ghz << units[unit_index];
    return clockfreq_str.str();
}

string GetPerformanceStr(double performance_tflops) {
    size_t unit_index = 4;
    ostringstream performance_str;
    vector<string> const units = {" FLOPS", " kFLOPS", " MFLOPS", " GFLOPS", " TFLOPS", " PFLOPS"};
    while (performance_tflops > 1000 && unit_index < units.size() - 1) {
        performance_tflops /= 1000;
        unit_index++;
    }
    while (performance_tflops < 1 && unit_index >= 0) {
        if (performance_tflops == 0) break;
        performance_tflops *= 1000;
        unit_index--;
    }
    performance_str << fixed << setprecision(2) << performance_tflops << units[unit_index];
    return performance_str.str();
}

string GetSizeStr(double size_byte) {
    size_t unit_index = 0;
    ostringstream capacity_str;
    vector<string> const units = {" Byte", " kB", " MB", " GB", " TB", " PB"};
    while (size_byte > 1024 && unit_index < units.size() - 1) {
        size_byte /= 1024;
        unit_index++;
    }
    capacity_str << fixed << setprecision(2) << size_byte << units[unit_index];
    return capacity_str.str();
}

}  // namespace adpart_sim