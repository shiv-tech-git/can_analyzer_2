#include "FileReader.h"
#include <fstream>
#include <iostream>


CM_TIMESTAMP_T FileReader::get_time(char* msg) {
    return msg[12] + msg[13] * 256 + msg[14] * 256 * 256;
}

CM_ID_T FileReader::get_id(char* msg) {
    uint32_t id = (uint8_t)msg[2];
    id <<= 8;
    id |= (uint8_t)msg[3];
    int tmp = 0;
    for (int i = 0; i < 5; i++) {
        tmp = id & 1;
        id >>= 1;
        id |= (tmp << 15);
    }
    return id;
}

CM_DATA_T FileReader::get_data(char* msg) {
    CM_DATA_T result;
    result.reserve(8);
    int byte_number = 8;
    for (int i = 0; i < 8; i++) {
        if (byte_number == 12) byte_number = 4;
        result.push_back(msg[byte_number]);
        byte_number++;
    }

    return result;
}

CM_DATA_SIZE_T FileReader::get_data_size(char* msg) {
    return msg[15] >> 4;
}

CM_CAN_NUMBER_T FileReader::get_can_number(char* msg) {
    return msg[15] &= 15;
}

FILE_DATA FileReader::parse_log_file(std::string file_path) {
    std::ifstream input(file_path, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    
    FILE_DATA result;
    result.full_path = file_path;
    result.name = get_file_name_from_path(file_path);
    
    std::unordered_map<CM_ID_T, std::vector<CAN_MSG> > msgs = get_log_file_msg(buffer);
    result.msgs = msgs;
    return result;
 
}

std::unordered_map<CM_ID_T, std::vector<CAN_MSG> > FileReader::get_log_file_msg(std::vector<unsigned char> buffer) {
    auto it = buffer.begin();
    std::unordered_map<CM_ID_T, std::vector<CAN_MSG> > result;
    while (it != buffer.end()) {
        add_can_msg(it, result);
        it += 16;
    }
    return result;
}

void FileReader::add_can_msg(std::vector<unsigned char>::iterator& it, std::unordered_map<CM_ID_T, std::vector<CAN_MSG> >& result) {
    CAN_MSG tmp;
    char* cm_ptr = (char*)(void*)&(*it);
    CM_ID_T id = get_id(cm_ptr);
    result[id].push_back({ id, get_data(cm_ptr), get_time(cm_ptr), get_can_number(cm_ptr) });
}


std::string FileReader::get_file_name_from_path(std::string full_path) {
    size_t start;
    size_t end = 0;
    char delim = '\\';
    std::vector<std::string> tmp;

    while ((start = full_path.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = full_path.find(delim, start);
        tmp.push_back(full_path.substr(start, end - start));
    }
    return tmp.back();
}