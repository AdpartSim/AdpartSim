#include "node/communicator.h"
#include "core/core.h"

using namespace std;

namespace adpart_sim {

// m_is_busy
bool Communicator::is_busy() { return m_is_busy; }

// m_parent
Application *Communicator::get_parent() { return m_parent; }

// m_metadata
shared_ptr<CommunicatorMetadata> Communicator::get_metadata() { return m_metadata; }

// m_algorithm
shared_ptr<Algorithm> Communicator::get_algorithm() { return m_algorithm; }

}  // namespace adpart_sim