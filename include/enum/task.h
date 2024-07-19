#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

enum class TaskType {
    INVALID,
    COMPUTE,
    COMMUNICATION,
    RESERVED,
};

TaskType GetTaskType(std::string type);

std::string GetTaskType(TaskType type);

}  // namespace adpart_sim

namespace adpart_sim {

enum class TaskStatus {
    INVALID,
    READY,
    RUNNING,
    COMPLETED,
    RESERVED,
};

TaskStatus GetTaskStatus(std::string status);

std::string GetTaskStatus(TaskStatus status);

}  // namespace adpart_sim
