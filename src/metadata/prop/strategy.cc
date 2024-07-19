#include "metadata/strategy.h"

using namespace std;

namespace adpart_sim {

// m_parent
Metadata *StrategyMetadata::get_parent() { return m_parent; }

// m_type
StrategyType StrategyMetadata::get_type() { return m_type; }

string StrategyMetadata::get_type_str() { return GetStrategyType(m_type); }

// m_epoch
size_t StrategyMetadata::get_epoch() { return m_epoch; }

// m_workload
string StrategyMetadata::get_workload() { return m_workload; }

}  // namespace adpart_sim