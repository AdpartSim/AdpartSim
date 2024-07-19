#include "node/accelerator.h"

using namespace std;

namespace adpart_sim {
// m_start_time
size_t IAccelerator::get_start_time_ns() { return m_start_time_ns; }

string IAccelerator::get_start_time_str() { return GetTimeStr(m_start_time_ns); }

// m_parent
Application *IAccelerator::get_parent() { return m_parent; }

// m_metadata
shared_ptr<AcceleratorMetadata> IAccelerator::get_metadata() { return m_metadata; }

}  // namespace adpart_sim

namespace adpart_sim {

// m_is_busy
bool Accelerator::is_busy() { return m_is_busy; }

// m_type
AcceleratorType Accelerator::get_type() { return m_type; }

string Accelerator::get_type_str() { return GetAcceleratorType(m_type); }

// m_accelerator

Application *Accelerator::get_parent() {
    ASSERT(m_accelerator);
    return m_accelerator->get_parent();
}

shared_ptr<IAccelerator> Accelerator::get_accelerator() { return m_accelerator; }

shared_ptr<AcceleratorMetadata> Accelerator::get_metadata() {
    ASSERT(m_accelerator);
    return m_accelerator->get_metadata();
}

}  // namespace adpart_sim