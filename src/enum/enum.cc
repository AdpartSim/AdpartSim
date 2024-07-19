#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

template <typename T>
T GetType(string type, unordered_map<string, T> map, T default_value) {
    for (auto &it : map) {
        regex type_regex("^" + it.first + "$", regex_constants::icase);
        if (regex_match(type, type_regex)) return it.second;
    }
    return default_value;
}

template <typename T>
string GetType(T type, unordered_map<string, T> map) {
    for (auto &it : map) {
        if (type == it.second) {
            return it.first;
        }
    }
    return "INVALID";
}

template string GetType<AcceleratorType>(  //
    AcceleratorType type,                  //
    unordered_map<string, AcceleratorType> map);

template AcceleratorType GetType<AcceleratorType>(  //
    string type,                                    //
    unordered_map<string, AcceleratorType> map,     //
    AcceleratorType default_value);

template string GetType<AlgorithmType>(  //
    AlgorithmType type,                  //
    unordered_map<string, AlgorithmType> map);

template AlgorithmType GetType<AlgorithmType>(  //
    string type,                                //
    unordered_map<string, AlgorithmType> map,   //
    AlgorithmType default_value);

template string GetType<ComputeDataType>(  //
    ComputeDataType type,                  //
    unordered_map<string, ComputeDataType> map);

template ComputeDataType GetType<ComputeDataType>(  //
    string type,                                    //
    unordered_map<string, ComputeDataType> map,     //
    ComputeDataType default_value);

template string GetType<CommunicationType>(  //
    CommunicationType type,                  //
    unordered_map<string, CommunicationType> map);

template CommunicationType GetType<CommunicationType>(  //
    string type,                                        //
    unordered_map<string, CommunicationType> map,       //
    CommunicationType default_value);

template string GetType<ComputeOpsType>(  //
    ComputeOpsType type,                  //
    unordered_map<string, ComputeOpsType> map);

template ComputeOpsType GetType<ComputeOpsType>(  //
    string type,                                  //
    unordered_map<string, ComputeOpsType> map,    //
    ComputeOpsType default_value);

template string GetType<NetworkType>(  //
    NetworkType type,                  //
    unordered_map<string, NetworkType> map);

template NetworkType GetType<NetworkType>(   //
    string type,                             //
    unordered_map<string, NetworkType> map,  //
    NetworkType default_value);

template string GetType<StrategyType>(  //
    StrategyType type,                  //
    unordered_map<string, StrategyType> map);

template StrategyType GetType<StrategyType>(  //
    string type,                              //
    unordered_map<string, StrategyType> map,  //
    StrategyType default_value);

template string GetType<TaskType>(  //
    TaskType type,                  //
    unordered_map<string, TaskType> map);

template TaskType GetType<TaskType>(      //
    string type,                          //
    unordered_map<string, TaskType> map,  //
    TaskType default_value);

template string GetType<TaskStatus>(  //
    TaskStatus type,                  //
    unordered_map<string, TaskStatus> map);

template TaskStatus GetType<TaskStatus>(    //
    string type,                            //
    unordered_map<string, TaskStatus> map,  //
    TaskStatus default_value);

template string GetType<TopologyType>(  //
    TopologyType type,                  //
    unordered_map<string, TopologyType> map);

template TopologyType GetType<TopologyType>(  //
    string type,                              //
    unordered_map<string, TopologyType> map,  //
    TopologyType default_value);

}  // namespace adpart_sim
