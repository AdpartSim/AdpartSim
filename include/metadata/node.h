#pragma once
#include "metadata/accelerator.h"
#include "metadata/communicator.h"
#include "metadata/memory.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Metadata;

class NodeMetadata {
   public:
    explicit NodeMetadata(Metadata *parent, JsonCpp const &json);

   public:
    // m_parent
    Metadata *get_parent();
    // m_count
    size_t get_count();
    // m_mdata_accelerators
    std::shared_ptr<AcceleratorMetadata> get_mdata_accelerator();
    // m_mdata_communicators
    std::shared_ptr<CommunicatorMetadata> get_mdata_communicator();
    // m_mdata_memory
    std::shared_ptr<MemoryMetadata> get_mdata_memory();

   private:
    Metadata *m_parent = nullptr;
    size_t m_count = 0;
    std::shared_ptr<AcceleratorMetadata> m_mdata_accelerator = nullptr;
    std::shared_ptr<CommunicatorMetadata> m_mdata_communicator = nullptr;
    std::shared_ptr<MemoryMetadata> m_mdata_memory = nullptr;
};

}  // namespace adpart_sim
