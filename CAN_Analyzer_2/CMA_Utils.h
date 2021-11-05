#pragma once
#include <vector>
#include <filesystem>
#include <map>
#include "CMA_Types.h"



#define MARK_ID 0xffff
#define EDGE_CHANGE_DELAY_MS 500

std::vector<CAN_MSG> get_marks(std::vector<CAN_MSG>& msgs);
EDGE_SEQUENCE get_edges(std::vector<CAN_MSG>& msgs, CM_DATA_SIZE_T byte_number, uint32_t edge_bouncing_perion);
std::vector<std::wstring> get_file_names_from_directory(std::wstring directory);
std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > filter_edge_sequence(FILE_DATA fd, bool (*predicate)(EDGE_SEQUENCE es));
std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > filter_byte_sequence(FILE_DATA fd, bool (*predicate)(BYTE_SEQUENCE bs));
void print_filtered_sequence(std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > id_byte);
bool has_pulse(EDGE_SEQUENCE es);
bool has_steps(EDGE_SEQUENCE es);
bool is_analog(BYTE_SEQUENCE es);
bool is_absolute_file_name(std::wstring file_name);
bool is_relative_file_name(std::wstring file_name);
bool is_directory(std::wstring dir_name);
bool is_VIN_char(uint8_t ch);
bool is_VIN_part(CM_DATA_T data);
std::wstring get_file_name_from_absolute_path(std::wstring abs_path);
bool file_exists(std::wstring file_path);
bool directory_exists(std::wstring dir);
void print_formatted_CAN_id(CM_ID_T id);