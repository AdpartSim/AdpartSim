#include "network/network.h"
#include "node/algorithm.h"
#include "node/application.h"
#include "node/communicator.h"
#include "node/node.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

class Algorithm_Direct : public IAlgorithm {
   public:
    Algorithm_Direct(Communicator *parent, unordered_map<shared_ptr<Network>, vector<shared_ptr<Device>>> networks)
        : IAlgorithm(parent, networks) {}

   private:
    size_t NotifyStart(size_t trunk_size = 1) {
        ASSERT(m_parent);
        ASSERT(m_parent->get_parent());
        ASSERT(m_parent->get_parent()->get_metadata());
        ASSERT(m_parent->get_parent()->get_metadata()->get_mdata_communicator());
        shared_ptr<NodeMetadata> metadata = m_parent->get_parent()->get_metadata();
        size_t communicator_buffersize = metadata->get_mdata_communicator()->get_buffer_size_mb() * 1048576;
        size_t size_byte = m_remaining_size_byte / trunk_size;
        if (size_byte > communicator_buffersize) {
            size_byte = communicator_buffersize;
        }
        return size_byte;
    }

    void NotifyFinished(size_t size_byte, size_t trunk_size = 1) {
        m_remaining_size_byte = size_byte > 0 ? m_remaining_size_byte - size_byte * trunk_size : 0;
        IAlgorithm::NotifyFinished();
    }

   public:
    void Send(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        size_t size_byte = NotifyStart();
        shared_ptr<Network> network = get_node_network(m_task->get_dst());
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 1:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToOne(size_byte, network, m_task->get_dst());
                break;
            case 2:
                if (algo_callback != AlgoCallback::SEND) break;
                SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte);
                break;
        }
    }

    void Receive(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        size_t size_byte = NotifyStart();
        shared_ptr<Network> network = get_node_network(m_task->get_dst());
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                WaitForOne(network, m_task->get_dst());
                break;
            case 1:
                if (algo_callback != AlgoCallback::RECV) break;
                SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte);
                break;
        }
    }

    void Barrier(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                for (auto &network_it : m_networks) {
                    BarrierWait(network_it.first);
                }
                break;
            default:
                NotifyFinished(0);
                break;
        }
    }

    void Reduce(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(m_task->get_root());
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        bool is_root = m_parent->get_parent()->get_parent()->get_node_id() == m_task->get_root();
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte * trunk_size);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToAll(size_byte, network);
                break;
            case 3:
                if (algo_callback != AlgoCallback::RECV) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 4:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                if (is_root)
                    WaitForAll(network);
                else
                    SendToAll(size_byte, network);
                break;
            case 5:
                if (is_root && algo_callback == AlgoCallback::RECV) {
                    OnChipMemoryCopy(size_byte * trunk_size);
                } else if (!is_root && algo_callback == AlgoCallback::SEND) {
                    SkipCurrentStatus();
                }
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void Gather(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(m_task->get_root());
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        bool is_root = m_parent->get_parent()->get_parent()->get_node_id() == m_task->get_root();
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                if (is_root) {
                    SkipCurrentStatus();
                } else {
                    OnChipMemoryCopy(size_byte);
                }
                break;
            case 2:
                if (is_root) {
                    WaitForAll(network);
                } else {
                    SendToOne(size_byte, network, m_task->get_root());
                }
                break;
            case 3:
                if (is_root && algo_callback == AlgoCallback::RECV)
                    SkipCurrentStatus();
                else if (!is_root && algo_callback == AlgoCallback::SEND)
                    SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void Scatter(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(m_task->get_root());
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        bool is_root = m_parent->get_parent()->get_parent()->get_node_id() == m_task->get_root();
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte * trunk_size);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                if (is_root) {
                    SendToAll(size_byte, network);
                } else {
                    WaitForOne(network, m_task->get_root());
                }
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void Broadcast(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(m_task->get_root());
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        bool is_root = m_parent->get_parent()->get_parent()->get_node_id() == m_task->get_root();
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte * trunk_size);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                if (is_root) {
                    SendToAll(size_byte, network);
                } else {
                    WaitForOne(network, m_task->get_root());
                }
                break;
            case 3:
                if (is_root && algo_callback == AlgoCallback::SEND) {
                    SendToAll(size_byte, network);
                } else if (!is_root && algo_callback == AlgoCallback::RECV) {
                    SendToAll(size_byte, network);
                }
                break;
            case 4:
                if (algo_callback == AlgoCallback::RECV) {
                    SkipCurrentStatus();
                }
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void AllToAll(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(0);
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte * trunk_size);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 3:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToAll(size_byte, network);
                break;
            case 4:
                if (algo_callback != AlgoCallback::RECV) break;
                SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void AllGather(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(0);
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToAll(size_byte, network);
                break;
            case 3:
                if (algo_callback != AlgoCallback::RECV) break;
                SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void AllReduce(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(0);
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToAll(size_byte, network);
                break;
            case 3:
                if (algo_callback != AlgoCallback::RECV) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 4:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToAll(size_byte, network);
                break;
            case 5:
                if (algo_callback != AlgoCallback::RECV) break;
                SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }

    void ReduceScatter(AlgoCallback algo_callback) override {
        __TRACE_LOG__
        shared_ptr<Network> network = get_node_network(0);
        size_t trunk_size = network->get_metadata()->get_node_count();
        size_t size_byte = NotifyStart(trunk_size);
        switch (m_step_status) {
            case 0:
                if (algo_callback != AlgoCallback::DEFAULT) break;
                BarrierWait(network);
                break;
            case 1:
                if (algo_callback != AlgoCallback::BARRIER) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 2:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SendToAll(size_byte, network);
                break;
            case 3:
                if (algo_callback != AlgoCallback::RECV) break;
                OnChipMemoryCopy(size_byte);
                break;
            case 4:
                if (algo_callback != AlgoCallback::MEMCPY) break;
                SkipCurrentStatus();
                break;
            default:
                NotifyFinished(size_byte, trunk_size);
                break;
        }
    }
};

}  // namespace adpart_sim
