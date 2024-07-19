#pragma once
#include "core/helper.h"
#include "metadata/switch.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Switch : public INodeHelper {
   public:
    explicit Switch(Core *parent, size_t node_id, std::shared_ptr<SwitchMetadata> metadata);

   public:
    void InitializeSwitch();

   public:
    // m_metadata
    std::shared_ptr<SwitchMetadata> get_metadata();

   private:
    std::shared_ptr<SwitchMetadata> m_metadata = nullptr;
};

}  // namespace adpart_sim