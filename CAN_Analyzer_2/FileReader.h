#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "DataStructures.h"

class FileReader {
public:
	FILE_DATA parse_log_file(std::string file_path);

private:
    std::string get_file_name_from_path(std::string full_path);
    std::unordered_map<CM_ID_T, std::vector<CAN_MSG> > get_log_file_msg(std::vector<unsigned char> buffer);
    void add_can_msg(std::vector<unsigned char>::iterator& it, std::unordered_map<CM_ID_T, std::vector<CAN_MSG> >& result);
    CM_TIMESTAMP_T get_time(char* msg);
    CM_ID_T get_id(char* msg);
    CM_DATA_T get_data(char* msg);
    CM_DATA_SIZE_T get_data_size(char* msg);
    CM_CAN_NUMBER_T get_can_number(char* msg);

};