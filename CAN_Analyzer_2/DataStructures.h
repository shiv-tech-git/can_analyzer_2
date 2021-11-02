#pragma once
#include <vector>
#include <unordered_map>

#define LEADING_EDGE 0
#define TRAILING_EDGE 1

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