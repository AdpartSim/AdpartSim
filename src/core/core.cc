#include "core/core.h"
#include "core/barrier.h"
#include "ns3/simulator.h"

using namespace std;

namespace adpart_sim {

Core::Core() {
    __TRACE_LOG__
    // m_mdata
    m_mdata = make_shared<Metadata>(this, JsonCpp::parse(g_configuration->get_config_content()));
    // m_strategy
    m_strategy = make_shared<Strategy>(this, m_mdata->get_mdata_strategy());
    // m_nodes
    shared_ptr<NodeMetadata> mdata_node = m_mdata->get_mdata_node();
    for (size_t i = 0; i < mdata_node->get_count(); i++) {
        m_nodes[i] = make_shared<Node>(this, i, mdata_node);
    }
    // m_switchs
    shared_ptr<SwitchMetadata> mdata_switch = m_mdata->get_mdata_switch();
    for (size_t i = 0; i < mdata_switch->get_count(); i++) {
        m_switchs[i] = make_shared<Switch>(this, i, mdata_switch);
    }
    // m_networks
    for (size_t i = 0; i < m_mdata->get_mdata_networks_count(); i++) {
        m_networks[i] = make_shared<Network>(this, i, m_mdata->get_mdata_network(i));
    }
}

void Core::SetupSimulator() {
    __TRACE_LOG__
    LOGI("Start Setup Simulator");
    // build network topology
    for (auto &network : m_networks) {
        network.second->BuildTopology(m_nodes, m_switchs);
    }
    // distrubute workload to node
    ASSERT(m_strategy);
    m_strategy->DistributeWorkload(m_nodes);
    // initialize switch configuration
    for (auto &switch_it : m_switchs) {
        switch_it.second->InitializeSwitch();
    }
    // initialize node configuration
    for (auto &node_it : m_nodes) {
        node_it.second->InitializeNode();
    }
}

void Core::RunSimulator() {
    __TRACE_LOG__
    LOGI("Start Run Simulator");
    ns3::Simulator::Run();
    ns3::Simulator::Destroy();
    // check node result
    bool result = true;
    for (auto &node_it : m_nodes) {
        bool result_it = node_it.second->CheckResult();
        result = result && result_it;
    }
    // output traffic heatmap
    g_configuration->heatmap_file << "traffic (byte),";
    for (size_t i = 0; i < m_nodes.size(); i++) {
        if (i > 0) {
            g_configuration->heatmap_file << ",";
        } 
        g_configuration->heatmap_file << "node_" << i;
    }
    g_configuration->heatmap_file << "\n";
    for (size_t i = 0; i < m_nodes.size(); i++) {
        g_configuration->heatmap_file << "node_" << i << ", ";
        for (size_t j = 0; j < m_nodes.size(); j++) {
            if (j > 0) {
                g_configuration->heatmap_file << ",";
            }
            g_configuration->heatmap_file << (i == j ? 0 : m_nodes[i]->GetTraffic(j));
        }
        g_configuration->heatmap_file << "\n";
    }
    LOGW_IF(!result, "Node execution result verification failed");
}

}  // namespace adpart_sim
