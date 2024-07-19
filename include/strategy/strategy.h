#pragma once
#include "enum/enum.h"
#include "metadata/metadata.h"
#include "node/node.h"
#include "task/task.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Core;

class IStrategy {
   public:
    explicit IStrategy(Core* parent, std::shared_ptr<StrategyMetadata> metadata);

   public:
    virtual void DistributeWorkload(std::unordered_map<size_t, std::shared_ptr<Node>>& nodes) = 0;

   public:
    // m_parent
    Core* get_parent();
    // m_metadata
    std::shared_ptr<StrategyMetadata> get_metadata();

   protected:
    Core* m_parent = nullptr;
    std::shared_ptr<StrategyMetadata> m_metadata = nullptr;
};

}  // namespace adpart_sim

namespace adpart_sim {

class Strategy {
   public:
    explicit Strategy(Core* parent, std::shared_ptr<StrategyMetadata> metadata);

   public:
    void DistributeWorkload(std::unordered_map<size_t, std::shared_ptr<Node>>& nodes);

   public:
    // m_type
    StrategyType get_type();
    std::string get_type_str();
    // m_strategy
    Core* get_parent();
    std::shared_ptr<StrategyMetadata> get_metadata();

   private:
    StrategyType m_type = StrategyType::INVALID;
    std::shared_ptr<IStrategy> m_strategy = nullptr;
};

}  // namespace adpart_sim