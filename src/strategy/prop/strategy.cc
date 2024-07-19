#include "strategy/strategy.h"

using namespace std;

namespace adpart_sim {

// m_metadata
Core *IStrategy::get_parent() { return m_parent; }
shared_ptr<StrategyMetadata> IStrategy::get_metadata() { return m_metadata; }

}  // namespace adpart_sim

namespace adpart_sim {

// m_type
StrategyType Strategy::get_type() { return m_type; }

string Strategy::get_type_str() { return GetStrategyType(m_type); }

// m_strategy

Core *Strategy::get_parent() {
    ASSERT(m_strategy);
    return m_strategy->get_parent();
}

shared_ptr<StrategyMetadata> Strategy::get_metadata() {
    ASSERT(m_strategy);
    return m_strategy->get_metadata();
}

}  // namespace adpart_sim