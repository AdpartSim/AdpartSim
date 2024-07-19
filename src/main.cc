#include <chrono>
#include "core/core.h"

using namespace std;
using namespace adpart_sim;

int main(int argc, char* argv[]) {
    chrono::system_clock::time_point start_time = chrono::system_clock::now();
    g_configuration = make_shared<Configuration>(argc, argv);
    shared_ptr<Core> core = make_shared<Core>();
    core->SetupSimulator();
    LOGI("Network Dims: " << core->get_networks_count() << ", Node Count: " << core->get_nodes_count()
                          << ", Switch Count: " << core->get_switchs_count());
    core->RunSimulator();
    float duration = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start_time).count();
    LOGI("Finished in " << fixed << setprecision(2) << duration / 1000.0 << " seconds with " << GetWarningCount()
                        << " warnings");
    return 0;
}
