#include "switch/switch.h"

using namespace std;

namespace adpart_sim {

SwitchMetadata::SwitchMetadata(Metadata *parent, JsonCpp const &json) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_count
    Json::Parse(m_count, json, "Count");
}

}  // namespace adpart_sim