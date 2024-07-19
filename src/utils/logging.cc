#include "utils/logging.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include "ns3/simulator.h"
#include "utils/env.h"
#include "utils/path.h"
#include "utils/unit.h"

using namespace std;

namespace adpart_sim {

static bool s_is_logv = false;
static pid_t s_pid = getpid();
static uint32_t s_current_tid = 1;
static uint64_t s_warning_count = 0;
static unordered_map<thread::id, int> s_short_tid = {};

string GetPrefix(string filename, size_t line, string pretty_function, string function) {
    ostringstream result;
    result << ' ';
    if (s_is_logv) {
        result << File::Filename(filename) << ':' << line << ", ";
        size_t left_paren_index = pretty_function.find('(');
        if (left_paren_index != string::npos) {
            size_t colon_index = pretty_function.substr(0, left_paren_index).rfind("::");
            if (colon_index != string::npos) {
                colon_index = colon_index + 2;
                result << pretty_function.substr(colon_index, left_paren_index - colon_index) << "::";
            }
        }
        result << function << "(), ";
    }
    return result.str();
}

void LoggingFormatter(ostream &stream, google::LogMessage const &message, void * /*data*/) {
    auto it = s_short_tid.find(message.thread_id());
    size_t now_ns = ns3::Simulator::Now().GetNanoSeconds();
    static const size_t max_time_ns = ns3::Years(1).GetNanoSeconds();
    if (it == s_short_tid.end()) s_short_tid[message.thread_id()] = s_current_tid++;
    if (google::GetLogSeverityName(message.severity())[0] == 'W') s_warning_count++;
    stream << '['                                                                                //
           << setw(4) << 1900 + message.time().year() << '/'                                     //
           << setw(2) << 1 + message.time().month() << '/'                                       //
           << setw(2) << message.time().day() << ' '                                             //
           << setw(2) << message.time().hour() << ':'                                            //
           << setw(2) << message.time().min() << ':'                                             //
           << setw(2) << message.time().sec() << '.'                                             //
           << setw(6) << message.time().usec() << " | "                                          //
           << setfill(' ') << setw(10) << GetTimeStr(now_ns < max_time_ns ? now_ns : 0) << ']';  //
    if (s_is_logv) {
        stream << ' '                                      //
               << setfill('0') << setw(6) << s_pid << ' '  //
               << setfill('0') << setw(2) << s_short_tid[message.thread_id()];
    }
}

void InitLogging(char const *bin_path) {
    FLAGS_stop_logging_if_full_disk = true;
    FLAGS_max_log_size = 1024;  // MB
    google::SetLogFilenameExtension(".log");

    // process log save path
    string log_path = Directory::Abspath(File::Dirname(string(bin_path)) + "/log/");
    log_path = GetEnvString("LOG_PATH", log_path);
    FLAGS_log_dir = log_path;

    // process log save filename
    ostringstream log_filename;
    FLAGS_log_file_header = false;
    FLAGS_timestamp_in_logfile_name = false;
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm *now_tm = localtime(&now);
    log_filename << log_path << "/AdpartSim." << put_time(now_tm, "%Y%m%d");
    google::SetLogDestination(google::GLOG_INFO, log_filename.str().c_str());
    google::SetLogDestination(google::GLOG_ERROR, log_filename.str().c_str());
    google::SetLogDestination(google::GLOG_FATAL, log_filename.str().c_str());
    google::SetLogDestination(google::GLOG_WARNING, log_filename.str().c_str());

    // process log output to console
    bool log_file = (int)GetEnvBool("LOG_FILE", true);
    if (!log_file) {
        FLAGS_logtostdout = true;
        FLAGS_logtostderr = true;
    } else {
        Directory::Create(log_path);
        FLAGS_alsologtostderr = true;
    }

    // process log output level
    FLAGS_minloglevel = 0;
    FLAGS_v = 0;
    string log_level = GetEnvString("LOG_LEVEL", "I");
    switch (log_level[0]) {
        case 'F':
        case 'f':
            FLAGS_minloglevel++;
        case 'E':
        case 'e':
            FLAGS_minloglevel++;
        case 'W':
        case 'w':
            FLAGS_minloglevel++;
            break;
        case 'V':
        case 'v':
            FLAGS_v = 1;
            s_is_logv = true;
            break;
    }

    // init google log module
    google::InstallPrefixFormatter(&LoggingFormatter);
    google::InitGoogleLogging(bin_path);
}

size_t GetWarningCount() { return s_warning_count; }

}  // namespace adpart_sim
