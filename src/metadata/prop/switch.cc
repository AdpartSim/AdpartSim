#include "metadata/switch.h"

using namespace std;

namespace adpart_sim {

// m_parent
Metadata *SwitchMetadata::get_parent() { return m_parent; }

// m_count
size_t SwitchMetadata::get_count() { return m_count; }

}  // namespace adpart_sim