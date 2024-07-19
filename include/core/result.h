#include "utils/configuration.h"

namespace adpart_sim {

class Task;

class Result {
   public:
    static void PrintTrace(std::shared_ptr<Task> task);
    static void PrintDetail(std::shared_ptr<Task> task, size_t epoch);

   private:
    static std::string GetTrace(std::string const &trace_template, std::map<std::string, std::string> trace_values);
};

}  // namespace adpart_sim