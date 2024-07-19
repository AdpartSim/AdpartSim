#pragma once
#include "enum/enum.h"
#include "metadata/metadata.h"
#include "task/task.h"
#include "utils/configuration.h"

namespace adpart_sim {

class Application;

class IAccelerator {
   public:
    explicit IAccelerator(Application *parent, std::shared_ptr<AcceleratorMetadata> metadata);

   public:
    virtual void Entry(std::function<void()> callback_func, std::shared_ptr<Task> task) = 0;

   public:
    // m_start_time
    size_t get_start_time_ns();
    std::string get_start_time_str();
    // m_parent
    Application *get_parent();
    // m_metadata
    std::shared_ptr<AcceleratorMetadata> get_metadata();

   protected:
    size_t m_start_time_ns = 0;
    Application *m_parent = nullptr;
    std::shared_ptr<AcceleratorMetadata> m_metadata = nullptr;

   protected:
    std::function<void()> m_callback_func = nullptr;
};

}  // namespace adpart_sim

namespace adpart_sim {

class Accelerator {
   public:
    explicit Accelerator(Application *parent, std::shared_ptr<AcceleratorMetadata> metadata);

   public:
    void Run(Application *caller, void (Application::*callback)(std::shared_ptr<Task>), std::shared_ptr<Task> task);

   private:
    void Callback(Application *caller, void (Application::*callback)(std::shared_ptr<Task>),
                  std::shared_ptr<Task> task);

   public:
    // m_is_busy
    bool is_busy();
    // m_type
    AcceleratorType get_type();
    std::string get_type_str();
    // m_accelerator
    Application *get_parent();
    std::shared_ptr<IAccelerator> get_accelerator();
    std::shared_ptr<AcceleratorMetadata> get_metadata();

   private:
    bool m_is_busy = false;
    AcceleratorType m_type = AcceleratorType::INVALID;
    std::shared_ptr<IAccelerator> m_accelerator = nullptr;
};

}  // namespace adpart_sim