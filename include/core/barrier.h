#pragma once
#include "utils/configuration.h"

namespace adpart_sim {

class Barrier {
   public:
    explicit Barrier(size_t total_count);

   public:
    void Clear();
    void Wait(std::function<void()> callback);

   private:
    size_t m_total_count = 0;
    size_t m_current_count = 0;
    std::vector<std::function<void()>> m_callbacks = {};
};

}  // namespace adpart_sim