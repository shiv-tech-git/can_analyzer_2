#pragma once
#include <vector>
#include <unordered_map>

typedef uint32_t CM_ID_T;
typedef uint64_t CM_TIMESTAMP_T;
typedef uint8_t CM_BYTE_T;
typedef std::vector<CM_BYTE_T> CM_DATA_T;
typedef uint8_t CM_DATA_SIZE_T;
typedef uint8_t CM_CAN_NUMBER_T;
typedef uint8_t EDGE_T;

typedef uint32_t CHANGES_COUNTER_T;

struct CAN_MSG
{
    CM_ID_T id;
    CM_DATA_T data;
    CM_TIMESTAMP_T timestamp;
    CM_CAN_NUMBER_T can_number;
};

struct FILE_DATA
{
    std::string name;
    std::string full_path;
    std::unordered_map<CM_ID_T, std::vector<CAN_MSG> > msgs;
};

struct change_point
{
    CM_TIMESTAMP_T timestamp;
    CM_DATA_T data;
    EDGE_T edge;
};

struct KEY_VALUE_ARG
{
    std::string key;
    std::string value;
};

struct USER_CMD {
    std::string cmd;
    std::vector<std::string> plain_args;
    std::vector<KEY_VALUE_ARG> key_value_args;
};

enum edge_type { leading, trailing };

struct EDGE {
    edge_type edge;
    CM_TIMESTAMP_T timestamp;
};

struct EDGE_SEQUENCE {
    CM_ID_T id;
    CM_DATA_SIZE_T byte_number;
    std::vector<EDGE> edges;
};