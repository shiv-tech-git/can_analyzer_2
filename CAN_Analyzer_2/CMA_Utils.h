#pragma once
#include <vector>
#include <filesystem>

#include "CMA_Types.h"


#define MARK_ID 0xffff
#define EDGE_CHANGE_DELAY_MS 500

std::vector<CAN_MSG> get_marks(std::vector<CAN_MSG>& msgs);
EDGE_SEQUENCE get_edges(std::vector<CAN_MSG>& msgs, CM_DATA_SIZE_T byte_number);
std::vector<std::string> get_file_names_from_directory(std::string directory);

bool is_absolute_file_name(std::string file_name);
bool is_relative_file_name(std::string file_name);
bool is_directory(std::string dir_name);
bool is_VIN_char(uint8_t ch);
bool is_VIN_part(CM_DATA_T data);