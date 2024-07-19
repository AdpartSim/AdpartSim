#include "core/core.h"
#include "node/application.h"
#include "node/communicator.h"

using namespace std;

namespace adpart_sim {

void Application::DoNextTask(shared_ptr<Task> task) {
    __TRACE_LOG__
    bool result = false;
    vector<shared_ptr<Task>> task_list = GetNextTask(task);
    for (auto &item : task_list) {
        switch (item->get_type()) {
            case TaskType::COMPUTE:
                if (!m_accelerator->is_busy()) {
                    m_accelerator->Run(this, &Application::DoNextTask, item);
                    result = true;
                }
                break;
            case TaskType::COMMUNICATION:
                if (!m_communicator->is_busy()) {
                    m_communicator->Run(this, &Application::DoNextTask, item);
                    result = true;
                }
                break;
            default:
                break;
        }
        if (!result) {
            m_current_task_index--;
            item->Reset();
        }
        LOGI_TIME(1, "Epoch: " << m_current_epoch + 1 << "/" << m_total_epoch << ", Tasks: " << m_current_task_index
                               << "/" << get_tasks_count());
    }
}

void Application::StartApplication() {
    __TRACE_LOG__
    m_current_epoch = 0;
    DoNextTask(nullptr);
}

void Application::StopApplication() { __TRACE_LOG__ }

}  // namespace adpart_sim