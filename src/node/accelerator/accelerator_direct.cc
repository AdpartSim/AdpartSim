#include "node/node.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

class Accelerator_Direct : public IAccelerator {
   public:
    Accelerator_Direct(Application* parent, shared_ptr<AcceleratorMetadata> metadata) : IAccelerator(parent, metadata) {
        __TRACE_LOG__
        //
    }

    void Entry(function<void()> callback_func, shared_ptr<Task> task) override {
        __TRACE_LOG__
        m_callback_func = callback_func;
        // do latency
        ns3::Time delay = ns3::NanoSeconds(m_metadata->get_latency_ns());
        ns3::Simulator::Schedule(delay, &Accelerator_Direct::DoCompute, this, task);
    }

   private:
    void DoCompute(shared_ptr<Task> task) {
        __TRACE_LOG__
        // do compute
        ns3::Time delay = ns3::NanoSeconds(task->get_compute_task()->get_runtime_ns());
        ns3::Simulator::Schedule(delay, m_callback_func);
    }
};

}  // namespace adpart_sim