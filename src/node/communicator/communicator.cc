#include "node/communicator.h"
#include "core/core.h"
#include "node/application.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

Communicator::Communicator(
    Application *parent,                                                                         //
    shared_ptr<CommunicatorMetadata> metadata,                                                   //
    std::unordered_map<std::shared_ptr<Network>, std::vector<std::shared_ptr<Device>>> networks  //
) {
    __TRACE_LOG__
    m_parent = parent;
    m_metadata = metadata;
    m_algorithm = make_shared<Algorithm>(this, networks);
}

void Communicator::Run(Application *caller,                              //
                       void (Application::*callback)(shared_ptr<Task>),  //
                       shared_ptr<Task> task) {
    __TRACE_LOG__
    ASSERT(m_algorithm);
    m_is_busy = true;
    auto callback_func = [this, caller, callback, task]() { this->Callback(caller, callback, task); };
    m_algorithm->Run(callback_func, task->get_communication_task());
}

void Communicator::Callback(Application *caller,                              //
                            void (Application::*callback)(shared_ptr<Task>),  //
                            shared_ptr<Task> task) {
    __TRACE_LOG__
    m_is_busy = false;
    ns3::Simulator::ScheduleNow(callback, caller, task);
}

}  // namespace adpart_sim
