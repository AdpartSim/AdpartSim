#include "enum/enum.h"

using namespace std;

namespace adpart_sim {

unordered_map<string, CommunicationType> const CommunicationTypeMap = {
    {"INVALID", CommunicationType::INVALID},                //
    {"P2P_SEND", CommunicationType::P2P_SEND},              //
    {"P2P_RECV", CommunicationType::P2P_RECV},              //
    {"BARRIER", CommunicationType::BARRIER},                //
    {"REDUCE", CommunicationType::REDUCE},                  //
    {"GATHER", CommunicationType::GATHER},                  //
    {"SCATTER", CommunicationType::SCATTER},                //
    {"BROADCAST", CommunicationType::BROADCAST},            //
    {"ALL_TO_ALL", CommunicationType::ALL_TO_ALL},          //
    {"ALL_GATHER", CommunicationType::ALL_GATHER},          //
    {"ALL_REDUCE", CommunicationType::ALL_REDUCE},          //
    {"REDUCE_SCATTER", CommunicationType::REDUCE_SCATTER},  //
    {"RESERVED", CommunicationType::RESERVED},              //
};

CommunicationType GetCommunicationType(string type) {
    return GetType(type, CommunicationTypeMap, CommunicationType::INVALID);
}

string GetCommunicationType(CommunicationType type) { return GetType(type, CommunicationTypeMap); }

bool IsAllToAll(CommunicationType type) {
    return type == CommunicationType::ALL_REDUCE         //
           || type == CommunicationType::ALL_GATHER      //
           || type == CommunicationType::ALL_TO_ALL      //
           || type == CommunicationType::REDUCE_SCATTER  //
           || type == CommunicationType::BARRIER;        //
}

bool IsAllToOne(CommunicationType type) {
    return type == CommunicationType::REDUCE      //
           || type == CommunicationType::GATHER;  //
}

bool IsOneToAll(CommunicationType type) {
    return type == CommunicationType::BROADCAST    //
           || type == CommunicationType::SCATTER;  //
}

bool IsOneToOne(CommunicationType type) {
    return type == CommunicationType::P2P_SEND  //
           || type == CommunicationType::P2P_RECV;
}

}  // namespace adpart_sim
