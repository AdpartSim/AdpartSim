#include "utils/configuration.h"
#include "ns3/command-line.h"

using namespace std;

namespace adpart_sim {

shared_ptr<Configuration> g_configuration = nullptr;

Configuration::Configuration(int argc, char *argv[]) {
    __TRACE_LOG__
    InitLogging(argv[0]);
    ns3::CommandLine cmd;
    string input_path = "config.json";
    string output_path = "result/";
    cmd.AddValue("input", "input configuration json file, default:", input_path);
    cmd.AddValue("output", "output result directory, default:", output_path);
    cmd.AddValue("trace", "save timeline trace to result directory, default:", m_trace_status);
    cmd.Parse(argc, argv);
    m_input_file = make_shared<File>(input_path);
    m_output_path = make_shared<Directory>(output_path);
    LOGE_IF(!m_input_file->exists(), "file: " << m_input_file->fullpath() << " does not exist");
    m_output_path->create();
    m_config_content = m_input_file->GetContent();
    SetCurrentConfigPath(m_input_file->dirname());
    if (m_trace_status) {
        timeline_file = ofstream(m_output_path->fullpath() + "/timeline.json");
        timeline_file << "[";
    }
    summary_file = ofstream(m_output_path->fullpath() + "/summary.csv");
    summary_file << "node_id,"
                    "compute_time_ns,"
                    "compute_time_str,"
                    "communication_time_ns,"
                    "communication_time_str,"
                    "explosed_communication_ns,"
                    "explosed_communication_str,"
                    "total_send_size_byte,"
                    "total_send_size_str,"
                    "total_recv_size_byte,"
                    "total_recv_size_str,"
                    "check_result\n";
    detail_file = ofstream(m_output_path->fullpath() + "/detail.csv");
    detail_file << "epoch,"
                   "node_id,"
                   "task_id,"
                   "task_type,"
                   "compute_data_type,"
                   "compute_ops_type,"
                   "compute_size_byte,"
                   "compute_size_str,"
                   "communication_type,"
                   "communication_size_byte,"
                   "communication_size_str,"
                   "start_time_ns,"
                   "start_time_str,"
                   "duration_time_ns,"
                   "duration_time_str,"
                   "task_status\n";
    traffic_file = ofstream(m_output_path->fullpath() + "/traffic_timing.csv");
    traffic_file << "time_ns,"
                    "time_str,"
                    "network_id,"
                    "src_node_id,"
                    "dst_node_id,"
                    "size_byte,"
                    "size_str\n";
    heatmap_file = ofstream(m_output_path->fullpath() + "/traffic_heatmap.csv");
    heatmap_file << "";
}

string Configuration::get_config_content() { return m_config_content; }

shared_ptr<File> Configuration::get_input_file() { return m_input_file; }

shared_ptr<Directory> Configuration::get_output_path() { return m_output_path; }

bool Configuration::get_trace_status() { return m_trace_status; }

Configuration::~Configuration() {
    if (m_trace_status) timeline_file << "{}]";
    google::ShutdownGoogleLogging();
}

}  // namespace adpart_sim
