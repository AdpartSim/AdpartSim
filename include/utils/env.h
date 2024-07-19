#pragma once
#include <string>

namespace adpart_sim {

std::string GetEnvString(std::string const &env_name, std::string default_value);
int GetEnvNumber(std::string const &env_name, int default_value = 0);
float GetEnvFloat(std::string const &env_name, float default_value = 0);
bool GetEnvBool(std::string const &env_name, bool default_value = false);

}  // namespace adpart_sim
