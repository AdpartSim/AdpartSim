#pragma once
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "utils/env.h"
#include "utils/json.h"
#include "utils/logging.h"
#include "utils/path.h"
#include "utils/unit.h"

#ifndef _MAX_SIZE_T_
#define _MAX_SIZE_T_ std::numeric_limits<size_t>::max()
#endif

namespace adpart_sim {

class Configuration {
   public:
    explicit Configuration(int argc, char *argv[]);
    ~Configuration();

   public:
    // m_config_content
    std::string get_config_content();
    // m_input_file
    std::shared_ptr<File> get_input_file();
    // m_output_path
    std::shared_ptr<Directory> get_output_path();
    std::ofstream timeline_file;
    std::ofstream summary_file;
    std::ofstream detail_file;
    std::ofstream traffic_file;
    std::ofstream heatmap_file;
    // m_trace_satus
    bool get_trace_status();

   private:
    std::shared_ptr<File> m_input_file = nullptr;
    std::shared_ptr<Directory> m_output_path = nullptr;
    std::string m_config_content = "empty_config_content";
    bool m_trace_status = true;
};

extern std::shared_ptr<Configuration> g_configuration;

}  // namespace adpart_sim
