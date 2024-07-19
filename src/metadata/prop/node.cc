#include "metadata/node.h"

using namespace std;

namespace adpart_sim {

// m_parent
Metadata *NodeMetadata::get_parent() { return m_parent; }

// m_count
size_t NodeMetadata::get_count() { return m_count; }

// m_mdata_accelerators
shared_ptr<AcceleratorMetadata> NodeMetadata::get_mdata_accelerator() { return m_mdata_accelerator; }

// m_mdata_communicators
std::shared_ptr<CommunicatorMetadata> NodeMetadata::get_mdata_communicator() { return m_mdata_communicator; }

// m_mdata_memory
std::shared_ptr<MemoryMetadata> NodeMetadata::get_mdata_memory() { return m_mdata_memory; }

}  // namespace adpart_sim