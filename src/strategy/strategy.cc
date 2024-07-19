#include "strategy/strategy.h"
#include "strategy_chakra.cc"
#include "strategy_testcase.cc"
using namespace std;

namespace adpart_sim {

IStrategy::IStrategy(Core *parent, shared_ptr<StrategyMetadata> metadata) {
    __TRACE_LOG__
    m_parent = parent;
    m_metadata = metadata;
}

}  // namespace adpart_sim

namespace adpart_sim {

Strategy::Strategy(Core *parent, shared_ptr<StrategyMetadata> metadata) {
    __TRACE_LOG__
    // m_type
    m_type = metadata->get_type();
    // m_strategy
    switch (m_type) {
        case StrategyType::CHAKRA:
            m_strategy = make_shared<Strategy_Chakra>(parent, metadata);
            break;
        case StrategyType::TESTCASE:
            m_strategy = make_shared<Strategy_TestCase>(parent, metadata);
            break;
        default:
            LOGE("unhandled type");
    }
}

void Strategy::DistributeWorkload(unordered_map<size_t, shared_ptr<Node>> &nodes) {
    __TRACE_LOG__
    ASSERT(m_strategy);
    m_strategy->DistributeWorkload(nodes);
    size_t epoch = get_metadata()->get_epoch();
    for (auto &node_it : nodes) {
        node_it.second->SetTotalEpoch(epoch);
    }
}

}  // namespace adpart_sim