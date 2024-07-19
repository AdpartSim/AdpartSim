#include "utils/env.h"
#include <getopt.h>
#include <regex>

using namespace std;

namespace adpart_sim {

string GetEnvString(string const& env_name, string default_value) {
    char const* env_str = getenv(env_name.c_str());
    return env_str != NULL ? string(env_str) : default_value;
}

int GetEnvNumber(string const& env_name, int default_value) {
    regex const number_reg("^(\\+|\\-)?\\d+$");
    char const* env_str = getenv(env_name.c_str());
    if (env_str != NULL) {
        string number_str(env_str);
        return regex_match(number_str, number_reg) ? atoi(env_str) : default_value;
    }
    return default_value;
}

float GetEnvFloat(string const& env_name, float default_value) {
    regex const float_reg("^(\\+|\\-)?\\d+(\\.\\d+)?$");
    char const* env_str = getenv(env_name.c_str());
    if (env_str != NULL) {
        string float_str(env_str);
        return regex_match(float_str, float_reg) ? atof(env_str) : default_value;
    }
    return default_value;
}

bool GetEnvBool(string const& env_name, bool default_value) {
    regex const bool_true_reg("^(1|T|True|ON)$", regex_constants::icase);
    regex const bool_false_reg("^(0|F|False|OFF)$", regex_constants::icase);
    char const* env_str = getenv(env_name.c_str());
    if (env_str != NULL) {
        string bool_str(env_str);
        if (regex_match(bool_str, bool_true_reg))
            return true;
        else if (regex_match(bool_str, bool_false_reg))
            return false;
    }
    return default_value;
}

}  // namespace adpart_sim
