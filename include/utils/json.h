#pragma once
#include <initializer_list>
#include <string>
#include "nlohmann/json.hpp"

using JsonCpp = nlohmann::json;

namespace adpart_sim {

class Json : public JsonCpp {
   public:
    static std::string GetStr(  //
        JsonCpp const &json,    //
        std::initializer_list<std::string> const &keys);

    static std::string GetStr(  //
        JsonCpp const &json,    //
        std::string const &key);

    static JsonCpp Get(       //
        JsonCpp const &json,  //
        std::initializer_list<std::string> const &keys);

    static JsonCpp Get(       //
        JsonCpp const &json,  //
        std::string const &key);

    static bool Contain(      //
        JsonCpp const &json,  //
        std::initializer_list<std::string> const &keys);

    static bool Contain(      //
        JsonCpp const &json,  //
        std::string const &key);

    template <typename T>
    static bool Parse(        //
        std::vector<T> &ref,  //
        JsonCpp const &json,  //
        std::initializer_list<std::string> const &keys);

    template <typename T>
    static bool Parse(        //
        std::vector<T> &ref,  //
        JsonCpp const &json,  //
        std::string const &key);

    template <typename T>
    static bool Parse(        //
        T &ref,               //
        JsonCpp const &json,  //
        std::initializer_list<std::string> const &keys);

    template <typename T>
    static bool Parse(        //
        T &ref,               //
        JsonCpp const &json,  //
        std::string const &key);

    static bool Parse(     //
        std::string &ref,  //
        JsonCpp const &json);
};

}  // namespace adpart_sim
