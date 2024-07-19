#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, TaskType> const TaskTypeMap = {
    {"INVALID", TaskType::INVALID},
    {"COMPUTE", TaskType::COMPUTE},
    {"COMMUNICATION", TaskType::COMMUNICATION},
    {"RESERVED", TaskType::RESERVED},
};

TaskType GetTaskType(string type) { return GetType(type, TaskTypeMap, TaskType::INVALID); }

string GetTaskType(TaskType type) { return GetType(type, TaskTypeMap); }

}  // namespace adpart_sim

namespace adpart_sim {

unordered_map<string, TaskStatus> const TaskStatusMap = {
    {"INVALID", TaskStatus::INVALID},      //
    {"READY", TaskStatus::READY},          //
    {"RUNNING", TaskStatus::RUNNING},      //
    {"COMPLETED", TaskStatus::COMPLETED},  //
    {"RESERVED", TaskStatus::RESERVED},
};

TaskStatus GetTaskStatus(string status) { return GetType(status, TaskStatusMap, TaskStatus::INVALID); }

string GetTaskStatus(TaskStatus status) { return GetType(status, TaskStatusMap); }

}  // namespace adpart_sim
