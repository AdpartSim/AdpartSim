#pragma once
#include "glog/logging.h"

namespace adpart_sim {

#define LOGV_TAG 1

std::string GetPrefix(std::string filename,         //
                      size_t line,                  //
                      std::string pretty_function,  //
                      std::string function);

#define _LOG_PREFIX_ GetPrefix(__FILE__, __LINE__, __PRETTY_FUNCTION__, __FUNCTION__)

#define LOGV(MESSAGE)                                     \
    do {                                                  \
        VLOG(LOGV_TAG) << "V" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGI(MESSAGE)                                \
    do {                                             \
        LOG(INFO) << "I" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGW(MESSAGE)                                   \
    do {                                                \
        LOG(WARNING) << "W" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGE(MESSAGE)                                  \
    do {                                               \
        LOG(ERROR) << "E" << _LOG_PREFIX_ << MESSAGE;  \
        LOG(ERROR) << "E" << _LOG_PREFIX_ << "exit()"; \
        exit(1);                                       \
    } while (0)

#define LOGV_IF(CONDITION, MESSAGE)                                     \
    do {                                                                \
        VLOG_IF(LOGV_TAG, CONDITION) << "V" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGI_IF(CONDITION, MESSAGE)                                \
    do {                                                           \
        LOG_IF(INFO, CONDITION) << "I" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGW_IF(CONDITION, MESSAGE)                                   \
    do {                                                              \
        LOG_IF(WARNING, CONDITION) << "W" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGE_IF(CONDITION, MESSAGE)                                 \
    do {                                                            \
        LOG_IF(ERROR, CONDITION) << "E" << _LOG_PREFIX_ << MESSAGE; \
        if (CONDITION) {                                            \
            LOG(ERROR) << "E" << _LOG_PREFIX_ << "exit()";          \
            exit(1);                                                \
        }                                                           \
    } while (0)

#define LOGV_EVERY(NUM, MESSAGE)                                       \
    do {                                                               \
        VLOG_EVERY_N(LOGV_TAG, NUM) << "E" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGI_EVERY(NUM, MESSAGE)                                  \
    do {                                                          \
        LOG_EVERY_N(INFO, NUM) << "I" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGI_TIME(SECOND, MESSAGE)                                   \
    do {                                                             \
        LOG_EVERY_T(INFO, SECOND) << "I" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define LOGI_FIRST(NUM, MESSAGE)                                  \
    do {                                                          \
        LOG_FIRST_N(INFO, NUM) << "I" << _LOG_PREFIX_ << MESSAGE; \
    } while (0)

#define ASSERT(PTR) LOGE_IF(PTR == nullptr, "nullptr error");

#define __TRACE_LOG__ LogTrace _log_trace_(__FILE__, __LINE__, __PRETTY_FUNCTION__, __FUNCTION__);

class LogTrace {
   public:
    LogTrace(std::string filename, size_t line, std::string pretty_function, std::string function) {
        m_prefix = GetPrefix(filename, line, pretty_function, function);
        VLOG(LOGV_TAG) << "V" << m_prefix << "E";
    }
    ~LogTrace() { VLOG(LOGV_TAG) << "V" << m_prefix << "X"; }

   private:
    std::string m_prefix;
};

void InitLogging(char const* bin_path);
size_t GetWarningCount();

}  // namespace adpart_sim
