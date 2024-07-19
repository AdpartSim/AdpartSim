#include "utils/json.h"
#include "utils/logging.h"

using namespace std;

namespace adpart_sim {

string Json::GetStr(      //
    JsonCpp const &json,  //
    initializer_list<string> const &keys) {
    JsonCpp json_str = Json::Get(json, keys);
    return json_str.empty() ? string() : json_str.get<string>();
}

string Json::GetStr(      //
    JsonCpp const &json,  //
    string const &key) {
    return Json::GetStr(json, {key});
}

JsonCpp Json::Get(        //
    JsonCpp const &json,  //
    initializer_list<string> const &keys) {
    JsonCpp current_json = json;
    auto it = keys.begin();
    string key = *it;
    while (current_json.contains(*it) && it != keys.end()) {
        if (it + 1 == keys.end()) {
            return current_json[*it];
        }
        if (current_json[*it].is_object()) {
            if (key.size() > 0) key.append("->");
            key.append(*it);
            current_json = current_json[*it];
            it++;
        } else {
            break;
        }
    }
    LOGW("The key [" << key << "] not found in json node");
    return JsonCpp::object();
}

JsonCpp Json::Get(        //
    JsonCpp const &json,  //
    string const &key) {
    return Json::Get(json, {key});
}

bool Json::Contain(       //
    JsonCpp const &json,  //
    initializer_list<string> const &keys) {
    return !Json::Get(json, keys).empty();
}

bool Json::Contain(       //
    JsonCpp const &json,  //
    string const &key) {
    return Json::Contain(json, {key});
}

template <typename T>
bool Json::Parse(         //
    T &ref,               //
    JsonCpp const &json,  //
    initializer_list<string> const &keys) {
    JsonCpp current_json = Json::Get(json, keys);
    bool result = !current_json.empty();
    if (result) ref = current_json.get<T>();
    return result;
}

template <typename T>
bool Json::Parse(         //
    T &ref,               //
    JsonCpp const &json,  //
    string const &key) {
    return Json::Parse(ref, json, {key});
}

bool Json::Parse(  //
    string &ref,   //
    JsonCpp const &json) {
    bool result = Json::Contain(json, ref);
    if (result) ref = json[ref].get<string>();
    return result;
}

template <typename T>
bool Json::Parse(         //
    vector<T> &ref,       //
    JsonCpp const &json,  //
    initializer_list<string> const &keys) {
    JsonCpp value = Json::Get(json, keys);
    bool result = !value.empty();
    if (result) {
        ref.clear();
        for (auto &it : value.items()) ref.push_back(it.value().get<T>());
    }
    return result;
}

template <typename T>
bool Json::Parse(         //
    vector<T> &ref,       //
    JsonCpp const &json,  //
    string const &key) {
    return Json::Parse(ref, json, {key});
}

template bool Json::Parse<string>(  //
    vector<string> &ref,            //
    JsonCpp const &json,            //
    initializer_list<string> const &keys);

template bool Json::Parse<uint64_t>(  //
    vector<uint64_t> &ref,            //
    JsonCpp const &json,              //
    initializer_list<string> const &keys);

template bool Json::Parse<uint32_t>(  //
    vector<uint32_t> &ref,            //
    JsonCpp const &json,              //
    initializer_list<string> const &keys);

template bool Json::Parse<double>(  //
    vector<double> &ref,            //
    JsonCpp const &json,            //
    initializer_list<string> const &keys);

template bool Json::Parse<float>(  //
    vector<float> &ref,            //
    JsonCpp const &json,           //
    initializer_list<string> const &keys);

template bool Json::Parse<long>(  //
    vector<long> &ref,            //
    JsonCpp const &json,          //
    initializer_list<string> const &keys);

template bool Json::Parse<bool>(  //
    vector<bool> &ref,            //
    JsonCpp const &json,          //
    initializer_list<string> const &keys);

template bool Json::Parse<int>(  //
    vector<int> &ref,            //
    JsonCpp const &json,         //
    initializer_list<string> const &keys);

template bool Json::Parse<string>(  //
    vector<string> &ref,            //
    JsonCpp const &json,            //
    string const &key);

template bool Json::Parse<uint32_t>(  //
    vector<uint32_t> &ref,            //
    JsonCpp const &json,              //
    string const &key);

template bool Json::Parse<uint64_t>(  //
    vector<uint64_t> &ref,            //
    JsonCpp const &json,              //
    string const &key);

template bool Json::Parse<double>(  //
    vector<double> &ref,            //
    JsonCpp const &json,            //
    string const &key);

template bool Json::Parse<float>(  //
    vector<float> &ref,            //
    JsonCpp const &json,           //
    string const &key);

template bool Json::Parse<long>(  //
    vector<long> &ref,            //
    JsonCpp const &json,          //
    string const &key);

template bool Json::Parse<bool>(  //
    vector<bool> &ref,            //
    JsonCpp const &json,          //
    string const &key);

template bool Json::Parse<int>(  //
    vector<int> &ref,            //
    JsonCpp const &json,         //
    string const &key);

template bool Json::Parse<string>(  //
    string &ref,                    //
    JsonCpp const &json,            //
    initializer_list<string> const &keys);

template bool Json::Parse<uint64_t>(  //
    uint64_t &ref,                    //
    JsonCpp const &json,              //
    initializer_list<string> const &keys);

template bool Json::Parse<uint32_t>(  //
    uint32_t &ref,                    //
    JsonCpp const &json,              //
    initializer_list<string> const &keys);

template bool Json::Parse<double>(  //
    double &ref,                    //
    JsonCpp const &json,            //
    initializer_list<string> const &keys);

template bool Json::Parse<float>(  //
    float &ref,                    //
    JsonCpp const &json,           //
    initializer_list<string> const &keys);

template bool Json::Parse<long>(  //
    long &ref,                    //
    JsonCpp const &json,          //
    initializer_list<string> const &keys);

template bool Json::Parse<bool>(  //
    bool &ref,                    //
    JsonCpp const &json,          //
    initializer_list<string> const &keys);

template bool Json::Parse<int>(  //
    int &ref,                    //
    JsonCpp const &json,         //
    initializer_list<string> const &keys);

template bool Json::Parse<string>(  //
    string &ref,                    //
    JsonCpp const &json,            //
    string const &key);

template bool Json::Parse<uint32_t>(  //
    uint32_t &ref,                    //
    JsonCpp const &json,              //
    string const &key);

template bool Json::Parse<uint64_t>(  //
    uint64_t &ref,                    //
    JsonCpp const &json,              //
    string const &key);

template bool Json::Parse<double>(  //
    double &ref,                    //
    JsonCpp const &json,            //
    string const &key);

template bool Json::Parse<float>(  //
    float &ref,                    //
    JsonCpp const &json,           //
    string const &key);

template bool Json::Parse<long>(  //
    long &ref,                    //
    JsonCpp const &json,          //
    string const &key);

template bool Json::Parse<bool>(  //
    bool &ref,                    //
    JsonCpp const &json,          //
    string const &key);

template bool Json::Parse<int>(  //
    int &ref,                    //
    JsonCpp const &json,         //
    string const &key);

}  // namespace adpart_sim