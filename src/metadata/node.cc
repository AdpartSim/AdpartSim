#include "metadata/node.h"

using namespace std;

namespace adpart_sim {

NodeMetadata::NodeMetadata(Metadata* parent, JsonCpp const& json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_count
    Json::Parse(m_count, json, "Count");
    // m_mdata_accelerators
    m_mdata_accelerator = make_shared<AcceleratorMetadata>(this, Json::Get(json, "Accelerator"));
    // m_mdata_communicators
    m_mdata_communicator = make_shared<CommunicatorMetadata>(this, Json::Get(json, "Communicator"));
    // m_mdata_memory
    m_mdata_memory = make_shared<MemoryMetadata>(this, Json::Get(json, "Memory"));
}

}  // namespace adpart_sim