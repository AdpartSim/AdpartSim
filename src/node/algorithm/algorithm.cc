#include "algorithm_direct.cc"
#include "core/core.h"
#include "network/network.h"
#include "node/node.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

IAlgorithm::IAlgorithm(Communicator *parent, unordered_map<shared_ptr<Network>, vector<shared_ptr<Device>>> networks) {
    __TRACE_LOG__
    // m_parent
    m_parent = parent;
    // m_step_status
    m_step_status = 0;
    // m_networks
    m_networks = networks;
    // m_devices and m_nodes
    size_t src_node_id = m_parent->get_parent()->get_parent()->get_node_id();
    for (auto &network_it : m_networks) {
        m_nodes[src_node_id].push_back(network_it.first);
        for (auto &device_it : network_it.second) {
            size_t node_id = device_it->get_dst_node()->get_node_id();
            m_nodes[node_id].push_back(network_it.first);
            m_devices[device_it->get_device_id()] = device_it;
            auto send_begin_callback = [this](size_t to_node_id) -> void { m_send_status[to_node_id] = false; };
            auto send_callback = [this](ns3::Ptr<ns3::Packet const> packet, size_t to_node_id) -> void {
                bool callback_check_result = true;
                m_send_status[to_node_id] = true;
                m_recv_status[to_node_id] = false;
                for (auto &send_status_it : m_send_status)
                    callback_check_result = callback_check_result && send_status_it.second;
                if (callback_check_result) ns3::Simulator::ScheduleNow([this]() { this->Run(AlgoCallback::SEND); });
            };
            auto recv_callback = [this](ns3::Ptr<ns3::Packet const> packet, size_t from_node_id) -> void {
                bool callback_check_result = true;
                m_recv_status[from_node_id] = true;
                for (auto &recv_status_it : m_recv_status)
                    callback_check_result = callback_check_result && recv_status_it.second;
                if (callback_check_result) {
                    if (m_timeout_event.IsPending()) m_timeout_event.Cancel();
                    ns3::Simulator::ScheduleNow([this]() { this->Run(AlgoCallback::RECV); });
                }
            };
            device_it->SetSendBeginCallback(send_begin_callback);
            device_it->SetSendCallback(send_callback);
            device_it->SetRecvCallback(recv_callback);
        }
    }
    // m_recv_status and m_send_status
    m_send_status.clear();
    m_recv_status.clear();
}

void IAlgorithm::BarrierWait(shared_ptr<Network> network) {
    m_step_status++;
    network->BarrierWait([this]() { this->Run(AlgoCallback::BARRIER); });
}

void IAlgorithm::SkipCurrentStatus() {
    m_step_status++;
    ns3::Simulator::ScheduleNow([this]() { this->Run(AlgoCallback::SKIP); });
}

void IAlgorithm::WaitForAll(shared_ptr<Network> network) {
    __TRACE_LOG__
    m_send_status.clear();
    m_recv_status.clear();
    for (auto &device_it : m_devices) {
        if (device_it.second->get_network_id() == network->get_id()) {
            size_t to_node_id = device_it.second->get_dst_node()->get_node_id();
            m_send_status[to_node_id] = true;
            m_recv_status[to_node_id] = false;
        }
    }
    m_timeout_event = ns3::Simulator::Schedule(ns3::Seconds(m_parent->get_metadata()->get_recv_timeout_s()), [this]() {
        m_step_status = _MAX_SIZE_T_;
        LOGW("WaitForAll Event Timeout after " << m_parent->get_metadata()->get_recv_timeout_s() << " seconds");
        this->Run(AlgoCallback::TIMEOUT);
    });
    m_step_status++;
}

void IAlgorithm::WaitForOne(shared_ptr<Network> network, size_t dst_node_id) {
    __TRACE_LOG__
    m_send_status.clear();
    m_recv_status.clear();
    m_send_status[dst_node_id] = true;
    m_recv_status[dst_node_id] = false;
    m_step_status++;
    m_timeout_event = ns3::Simulator::Schedule(ns3::Seconds(m_parent->get_metadata()->get_recv_timeout_s()), [this]() {
        m_step_status = _MAX_SIZE_T_;
        LOGW("WaitForOne Event Timeout after " << m_parent->get_metadata()->get_recv_timeout_s() << " seconds");
        this->Run(AlgoCallback::TIMEOUT);
    });
}

void IAlgorithm::SendToAll(size_t size_byte, shared_ptr<Network> network) {
    __TRACE_LOG__
    m_send_status.clear();
    m_recv_status.clear();
    bool result = false;
    for (auto &device_it : m_devices) {
        if (device_it.second->get_network_id() == network->get_id()) {
            result = device_it.second->Send(size_byte);
        }
    }
    m_step_status++;
    LOGE_IF(!result, "failed to send");
}

void IAlgorithm::SendToOne(size_t size_byte, std::shared_ptr<Network> network, size_t dst_node_id) {
    __TRACE_LOG__
    m_send_status.clear();
    m_recv_status.clear();
    bool result = false;
    for (auto &device_it : m_devices) {
        if (device_it.second->get_network_id() == network->get_id()
            && device_it.second->get_dst_node()->get_node_id() == dst_node_id) {
            result = device_it.second->Send(size_byte);
            break;
        }
    }
    m_step_status++;
    LOGE_IF(!result, "failed to send");
}

void IAlgorithm::OnChipMemoryCopy(size_t size_byte) {
    m_step_status++;
    ASSERT(m_parent);
    ASSERT(m_parent->get_parent());
    ASSERT(m_parent->get_parent()->get_metadata());
    ASSERT(m_parent->get_parent()->get_metadata()->get_mdata_memory());
    shared_ptr<NodeMetadata> metadata = m_parent->get_parent()->get_metadata();
    double memory_bandwidth = metadata->get_mdata_memory()->get_bandwidth_gbps();
    double memory_latency = metadata->get_mdata_memory()->get_latency_ns();
    size_t delay_ns = memory_latency + (size_byte * 8.0) / memory_bandwidth;
    ns3::Simulator::Schedule(ns3::NanoSeconds(delay_ns), [this]() { this->Run(AlgoCallback::MEMCPY); });
}

void IAlgorithm::NotifyFinished() {
    m_send_status.clear();
    m_recv_status.clear();
    if (m_remaining_size_byte > 0) {
        m_step_status = 0;
        ns3::Simulator::ScheduleNow([this]() { this->Run(AlgoCallback::DEFAULT); });
    } else {
        m_is_finished = true;
        ns3::Simulator::ScheduleNow(m_callback_func);
    }
}

void IAlgorithm::Run(AlgoCallback type) {
    if (m_is_finished) return;
    switch (m_task->get_communication_type()) {
        case CommunicationType::P2P_SEND:
            Send(type);
            break;
        case CommunicationType::P2P_RECV:
            Receive(type);
            break;
        case CommunicationType::BARRIER:
            m_remaining_size_byte = 0;
            Barrier(type);
            break;
        case CommunicationType::REDUCE:
            Reduce(type);
            break;
        case CommunicationType::GATHER:
            Gather(type);
            break;
        case CommunicationType::SCATTER:
            Scatter(type);
            break;
        case CommunicationType::BROADCAST:
            Broadcast(type);
            break;
        case CommunicationType::ALL_TO_ALL:
            AllToAll(type);
            break;
        case CommunicationType::ALL_GATHER:
            AllGather(type);
            break;
        case CommunicationType::ALL_REDUCE:
            AllReduce(type);
            break;
        case CommunicationType::REDUCE_SCATTER:
            ReduceScatter(type);
            break;
        default:
            LOGE("unhandled type");
    }
}

void IAlgorithm::Run(                //
    function<void()> callback_func,  //
    shared_ptr<CommunicationTask> task) {
    __TRACE_LOG__
    m_task = task;
    m_step_status = 0;
    m_is_finished = false;
    m_callback_func = callback_func;
    m_remaining_size_byte = m_task->get_size_byte();
    m_send_status.clear();
    m_recv_status.clear();
    ns3::Simulator::ScheduleNow([this]() { this->Run(AlgoCallback::DEFAULT); });
}

}  // namespace adpart_sim

namespace adpart_sim {

Algorithm::Algorithm(Communicator *parent, unordered_map<shared_ptr<Network>, vector<shared_ptr<Device>>> networks) {
    __TRACE_LOG__
    ASSERT(parent);
    ASSERT(parent->get_metadata());
    // m_type
    m_type = parent->get_metadata()->get_algorithm_type();
    // m_algorithm
    switch (m_type) {
        case AlgorithmType::DIRECT:
            m_algorithm = make_shared<Algorithm_Direct>(parent, networks);
            break;
        default:
            LOGE("unhandled type");
    }
}

void Algorithm::Run(                 //
    function<void()> callback_func,  //
    shared_ptr<CommunicationTask> task) {
    __TRACE_LOG__
    ASSERT(m_algorithm);
    m_algorithm->Run(callback_func, task);
}

}  // namespace adpart_sim
