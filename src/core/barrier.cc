#include "core/barrier.h"

using namespace std;

namespace adpart_sim {

Barrier::Barrier(size_t total_count) {
    __TRACE_LOG__
    m_total_count = total_count;
}

void Barrier::Clear() {
    __TRACE_LOG__
    m_current_count = 0;
    m_callbacks.clear();
}

void Barrier::Wait(function<void()> callback) {
    __TRACE_LOG__
    m_current_count++;
    m_callbacks.push_back(callback);
    if (m_current_count >= m_total_count) {
        for (auto &callback : m_callbacks) {
            callback();
        }
        Clear();
    }
}

}  // namespace adpart_sim