#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

class Metadata;

class SwitchMetadata {
   public:
    explicit SwitchMetadata(Metadata *parent, JsonCpp const &json);

   public:
    // m_parent
    Metadata *get_parent();
    // m_count
    size_t get_count();

   private:
    Metadata *m_parent = nullptr;
    size_t m_count = 0;
};

}  // namespace adpart_sim
