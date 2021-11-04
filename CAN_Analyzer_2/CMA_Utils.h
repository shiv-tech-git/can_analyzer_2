#pragma once
#include <vector>
#include <filesystem>

#include "CMA_Types.h"


#define MARK_ID 0xffff
#define EDGE_CHANGE_DELAY_MS 500

std::vector<CAN_MSG> get_marks(std::vector<CAN_MSG>& msgs);
EDGE_SEQUENCE get_edges(std::vector<CAN_MSG>& msgs, CM_DATA_SIZE_T byte_number);
std::vector<std::wstring> get_file_names_from_directory(std::wstring directory);

bool is_absolute_file_name(std::wstring file_name);
bool is_relative_file_name(std::wstring file_name);
bool is_directory(std::wstring dir_name);
bool is_VIN_char(uint8_t ch);
bool is_VIN_part(CM_DATA_T data);
std::wstring get_file_name_from_absolute_path(std::wstring abs_path);
bool file_exists(std::wstring file_path);
bool directory_exists(std::wstring dir);