#include "core/result.h"
#include "task/task.h"

using namespace std;

namespace adpart_sim {

string const k_trace_template = R"({
    "name": "$NAME",
    "ph": "X",
    "pid": "$PID",
    "tid": "$TID",
    "ts": $TS,
    "dur": $DUR,
    "args": {$ARGS}
},)";

string const k_trace_task_template = R"(
    "task_id": "$TASK_ID",
    "task_name": "$TASK_NAME",
    "task_status": "$TASK_STATUS"
)";

string const k_trace_compute_template = R"(
    "compute_type": "$COMPUTE_TYPE",
    "compute_data_type": "$COMPUTE_DATA_TYPE",
    "compute_ops_type": "$COMPUTE_OPS_TYPE",
    "compute_size": "$COMPUTE_SIZE",
    "compute_runtime_ns": "$COMPUTE_RUNTIME"
)";

string const k_trace_communication_template = R"(
    "comm_type": "$COMM_TYPE",
    "comm_size": "$COMM_SIZE",
    "comm_root": $COMM_ROOT,
    "comm_src": $COMM_SRC,
    "comm_dst": $COMM_DST
)";

string Result::GetTrace(string const &trace_template, map<string, string> trace_values) {
    string trace = trace_template;
    for (auto &item : trace_values) {
        size_t pos = trace.find(item.first);
        if (pos != string::npos) {
            trace = trace.replace(pos, item.first.size(), item.second);
        }
    }
    return trace;
}

void Result::PrintTrace(shared_ptr<Task> task) {
    if (!g_configuration->get_trace_status()) return;
    map<string, string> trace_args_task = {
        {"$TASK_ID", to_string(task->get_task_id())},
        {"$TASK_NAME", task->get_task_name()},
        {"$TASK_STATUS", task->get_status_str()},
    };
    string trace_args_task_str = GetTrace(k_trace_task_template, trace_args_task);
    if (task->get_type() == TaskType::COMPUTE) {
        map<string, string> trace_args_compute = {
            {"$COMPUTE_DATA_TYPE", task->get_compute_task()->get_data_type_str()},
            {"$COMPUTE_OPS_TYPE", task->get_compute_task()->get_ops_type_str()},
            {"$COMPUTE_SIZE", task->get_compute_task()->get_size_str()},
            {"$COMPUTE_RUNTIME", task->get_compute_task()->get_runtime_str()},
        };
        trace_args_task_str += "," + GetTrace(k_trace_compute_template, trace_args_compute);
    } else if (task->get_type() == TaskType::COMMUNICATION) {
        map<string, string> trace_args_communication = {
            {"$COMM_TYPE", task->get_communication_task()->get_communication_type_str()},
            {"$COMM_SIZE", task->get_communication_task()->get_size_str()},
            {"$COMM_ROOT", to_string(task->get_communication_task()->get_root())},
            {"$COMM_SRC", to_string(task->get_communication_task()->get_src())},
            {"$COMM_DST", to_string(task->get_communication_task()->get_dst())},
        };
        trace_args_task_str += "," + GetTrace(k_trace_communication_template, trace_args_communication);
    } else {
        LOGW("unprocessed task type");
    }
    map<string, string> trace_values = {
        {"$NAME", task->get_task_name()},
        {"$PID", "Node_" + to_string(task->get_node_id())},
        {"$TID", task->get_type_str()},
        {"$TS", to_string(task->get_start_time_ns() / 1000.0)},
        {"$DUR", to_string(task->get_duration_time_ns() / 1000.0)},
        {"$ARGS", trace_args_task_str},
    };
    g_configuration->timeline_file << GetTrace(k_trace_template, trace_values);
}

void Result::PrintDetail(shared_ptr<Task> task, size_t epoch) {
    g_configuration->detail_file                                                //
        << epoch << ","                                                         // epoch
        << task->get_node_id() << ","                                           // node_id
        << task->get_task_id() << ","                                           // task_id
        << task->get_type_str() << ","                                          // task_type
        << task->get_compute_task()->get_data_type_str() << ","                 // compute_data_type
        << task->get_compute_task()->get_ops_type_str() << ","                  // compute_ops_type
        << task->get_compute_task()->get_size_byte() << ","                     // compute_size_byte
        << task->get_compute_task()->get_size_str() << ","                      // compute_size_str
        << task->get_communication_task()->get_communication_type_str() << ","  // communication_type
        << task->get_communication_task()->get_size_byte() << ","               // communication_size_byte
        << task->get_communication_task()->get_size_str() << ","                // communication_size_str
        << task->get_start_time_ns() << ","                                     // start_time_ns
        << task->get_start_time_str() << ","                                    // start_time_str
        << task->get_duration_time_ns() << ","                                  // duration_time_ns
        << task->get_duration_time_str() << ","                                 // duration_time_str
        << task->get_status_str() << "\n";                                      // task_status
}

}  // namespace adpart_sim