#pragma once
#include "core/helper.h"
#include "enum/enum.h"
#include "ns3/event-id.h"
#include "task/task.h"

namespace adpart_sim {

class Network;
class Communicator;

enum class AlgoCallback {
    INVALID,
    SKIP,
    SEND,
    RECV,
    MEMCPY,
    BARRIER,
    TIMEOUT,
    DEFAULT,
    RESERVED,
};

class IAlgorithm {
   public:
    explicit IAlgorithm(       //
        Communicator *parent,  //
        std::unordered_map<std::shared_ptr<Network>, std::vector<std::shared_ptr<Device>>> networks);

   public:
    void Run(AlgoCallback type);
    void Run(std::function<void()> callback_func, std::shared_ptr<CommunicationTask> task);

   protected:
    void SkipCurrentStatus();
    void BarrierWait(std::shared_ptr<Network> network);
    void WaitForAll(std::shared_ptr<Network> network);
    void WaitForOne(std::shared_ptr<Network> network, size_t dst_node_id);
    void SendToAll(size_t size_byte, std::shared_ptr<Network> network);
    void SendToOne(size_t size_byte, std::shared_ptr<Network> network, size_t dst_node_id);

   protected:
    void NotifyFinished();
    void OnChipMemoryCopy(size_t size_byte);

   public:
    virtual void Send(AlgoCallback algo_callback) = 0;
    virtual void Receive(AlgoCallback algo_callback) = 0;
    virtual void Barrier(AlgoCallback algo_callback) = 0;
    virtual void Reduce(AlgoCallback algo_callback) = 0;
    virtual void Gather(AlgoCallback algo_callback) = 0;
    virtual void Scatter(AlgoCallback algo_callback) = 0;
    virtual void Broadcast(AlgoCallback algo_callback) = 0;
    virtual void AllToAll(AlgoCallback algo_callback) = 0;
    virtual void AllGather(AlgoCallback algo_callback) = 0;
    virtual void AllReduce(AlgoCallback algo_callback) = 0;
    virtual void ReduceScatter(AlgoCallback algo_callback) = 0;

   public:
    // m_parent
    Communicator *get_parent();
    // m_start_time_ns
    size_t get_start_time_ns();
    std::string get_start_time_str();
    // m_networks
    std::unordered_map<std::shared_ptr<Network>, std::vector<std::shared_ptr<Device>>> get_networks();
    size_t get_networks_count();
    std::vector<std::shared_ptr<Device>> get_devices(std::shared_ptr<Network> network);
    size_t get_devices_count(std::shared_ptr<Network> network);
    std::vector<std::shared_ptr<Device>> get_devices(size_t network_id);
    size_t get_devices_count(size_t network_id);
    // m_devices
    std::shared_ptr<Device> get_device(size_t device_id);
    // m_nodes
    std::vector<std::shared_ptr<Network>> get_node_networks(size_t node_id);
    std::shared_ptr<Network> get_node_network(size_t node_id);

   protected:
    size_t m_step_status = 0;
    size_t m_start_time_ns = 0;
    size_t m_remaining_size_byte = 0;
    Communicator *m_parent = nullptr;
    std::function<void()> m_callback_func = nullptr;
    std::shared_ptr<CommunicationTask> m_task = nullptr;
    std::unordered_map<size_t, bool> m_send_status = {};
    std::unordered_map<size_t, bool> m_recv_status = {};
    std::unordered_map<std::shared_ptr<Network>, std::vector<std::shared_ptr<Device>>> m_networks = {};

   private:
    ns3::EventId m_timeout_event;
    bool m_is_finished = false;
    std::unordered_map<size_t, std::shared_ptr<Device>> m_devices = {};
    std::unordered_map<size_t, std::vector<std::shared_ptr<Network>>> m_nodes = {};
};

class Algorithm {
   public:
    explicit Algorithm(        //
        Communicator *parent,  //
        std::unordered_map<std::shared_ptr<Network>, std::vector<std::shared_ptr<Device>>> networks);

   public:
    void Run(std::function<void()> callback_func, std::shared_ptr<CommunicationTask> task);

   public:
    // m_type
    AlgorithmType get_type();
    std::string get_type_str();
    // m_algorithm
    Communicator *get_parent();
    std::shared_ptr<IAlgorithm> get_algorithm();

   protected:
    AlgorithmType m_type = AlgorithmType::INVALID;
    std::shared_ptr<IAlgorithm> m_algorithm = nullptr;
};

}  // namespace adpart_sim
