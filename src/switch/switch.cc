#include "switch/switch.h"

using namespace std;

namespace adpart_sim {

Switch::Switch(Core *parent, size_t node_id, shared_ptr<SwitchMetadata> metadata) : INodeHelper(parent, node_id) {
    __TRACE_LOG__
    m_metadata = metadata;
}

void Switch::InitializeSwitch() {
    __TRACE_LOG__
    // TODO
}

}  // namespace adpart_sim
