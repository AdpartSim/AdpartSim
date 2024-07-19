#include "metadata/strategy.h"

using namespace std;

namespace adpart_sim {

StrategyMetadata::StrategyMetadata(Metadata *parent, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_type
    m_type = GetStrategyType(Json::GetStr(json, "Type"));
    // m_epoch
    Json::Parse(m_epoch, json, "Epoch");
    // m_workload
    Json::Parse(m_workload, json, "Workload");
}

}  // namespace adpart_sim