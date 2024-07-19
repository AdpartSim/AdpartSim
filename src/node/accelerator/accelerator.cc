#include "node/accelerator.h"
#include "accelerator_direct.cc"
#include "node/application.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

IAccelerator::IAccelerator(Application *parent, shared_ptr<AcceleratorMetadata> metadata) {
    __TRACE_LOG__
    m_parent = parent;
    m_metadata = metadata;
}

}  // namespace adpart_sim

namespace adpart_sim {

Accelerator::Accelerator(Application *parent, shared_ptr<AcceleratorMetadata> metadata) {
    __TRACE_LOG__
    // m_type
    m_type = metadata->get_type();
    // m_accelerator
    switch (m_type) {
        case AcceleratorType::DIRECT:
            m_accelerator = make_shared<Accelerator_Direct>(parent, metadata);
            break;
        default:
            LOGE("unhandled type");
    }
}

void Accelerator::Run(Application *caller, void (Application::*callback)(shared_ptr<Task>), shared_ptr<Task> task) {
    __TRACE_LOG__
    ASSERT(m_accelerator);
    m_is_busy = true;
    auto callback_func = [this, caller, callback, task]() { this->Callback(caller, callback, task); };
    m_accelerator->Entry(callback_func, task);
}

void Accelerator::Callback(Application *caller, void (Application::*callback)(shared_ptr<Task>),
                           shared_ptr<Task> task) {
    __TRACE_LOG__
    m_is_busy = false;
    ns3::Simulator::ScheduleNow(callback, caller, task);
}

}  // namespace adpart_sim