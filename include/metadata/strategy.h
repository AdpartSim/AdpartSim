#pragma once
#include "enum/enum.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Metadata;

class StrategyMetadata {
   public:
    explicit StrategyMetadata(Metadata *parent, JsonCpp const &json);

   public:
    // m_parent
    Metadata *get_parent();
    // m_type
    StrategyType get_type();
    std::string get_type_str();
    // m_epoch
    size_t get_epoch();
    // m_workload
    std::string get_workload();

   private:
    Metadata *m_parent = nullptr;
    StrategyType m_type = StrategyType::INVALID;
    size_t m_epoch = 0;
    std::string m_workload = std::string();
};

}  // namespace adpart_sim
