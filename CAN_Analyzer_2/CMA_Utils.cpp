#include "CMA_Utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <locale>
#include <codecvt>
#include <iostream>
#include <map>
#include <set>

std::vector<CAN_MSG> get_marks(std::vector<CAN_MSG>& msgs) {
	std::vector<CAN_MSG> result;
	for (auto it = msgs.begin(); it != msgs.end(); it++) {
		if (it->id == MARK_ID) {
			if (result.size() == 0) {
				result.push_back(*it);
			}
			else if (std::abs((int)(it->timestamp - result.back().timestamp)) > 500) {
				CM_TIMESTAMP_T last_time = result.back().timestamp;
				CM_TIMESTAMP_T current_time = it->timestamp;
				result.push_back(*it);
			}
		}
	}
	return result;
}

EDGE_SEQUENCE get_edges(std::vector<CAN_MSG>& msgs, CM_DATA_SIZE_T byte_number, uint32_t edge_bouncing_perion = EDGE_CHANGE_DELAY_MS) {
	EDGE_SEQUENCE result;
	result.id = msgs[0].id;
	result.byte_number = byte_number;

	auto it = msgs.begin();
	auto last = it;
	it++;
	for (; it != msgs.end(); it++) {
		if (it->data[byte_number] != last->data[byte_number] && (uint32_t)std::abs((int)(it->timestamp - last->timestamp)) > edge_bouncing_perion) {
			if (it->data[byte_number] > last->data[byte_number]) {
				result.edges.push_back({ leading, it->timestamp, last->data[byte_number], it->data[byte_number] });
			}
			else {
				result.edges.push_back({ trailing, it->timestamp, last->data[byte_number], it->data[byte_number] });
			}
			last = it;
		}
	}
	return result;
}

BYTE_SEQUENCE get_bytes(std::vector<CAN_MSG>& msgs, CM_DATA_SIZE_T byte_number) {
	BYTE_SEQUENCE result;
	result.id = msgs[0].id;
	result.byte_number = byte_number;

	for (auto it = msgs.begin(); it != msgs.end(); it++) {
		result.bytes.push_back(it->data[byte_number]);
	}
	return result;
}

std::vector<std::wstring> get_file_names_from_directory(std::wstring directory) {
	std::vector<std::wstring> file_names;

	for (const auto& file : std::filesystem::directory_iterator(directory)) {
		std::wstring file_name = file.path().wstring();
		if (file_name.find(L".bin") != std::wstring::npos) {
			file_names.push_back(file_name);
		}
	}
	return file_names;
}

bool is_absolute_file_name(std::wstring file_name) {
	if (file_name.find(L".bin") != std::wstring::npos && file_name.find(L"\\") != std::wstring::npos)
		return true;
	return false;
}

bool is_relative_file_name(std::wstring file_name) {
	if (file_name.find(L".bin") != std::wstring::npos && file_name.find(L"\\") == std::wstring::npos)
		return true;
	return false;
}

bool is_directory(std::wstring dir_name) {
	if (dir_name.find(L".bin") == std::wstring::npos && 
		dir_name.find(L"\\") != std::wstring::npos &&
		dir_name.find(L":") != std::wstring::npos)
		return true;
	return false;
}

std::wstring get_file_name_from_absolute_path(std::wstring abs_path) {
	size_t pos = abs_path.rfind('\\');
	return abs_path.substr(++pos);
}


bool is_VIN_char(uint8_t ch) {
	if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		return true;
	return false;
}

bool is_VIN_part(CM_DATA_T data) {
	for (auto b : data) {
		if (!is_VIN_char(b)) return false;
	}
	return true;
}

bool file_exists(std::wstring file_path) {
	return std::filesystem::exists(file_path);
}

bool directory_exists(std::wstring dir) {
	//struct stat info;
	//if (stat(tmp.c_str(), &info) != 0)
	//	return false;

	//if (info.st_mode & S_IFDIR)
	//	return true;
	return std::filesystem::exists(dir);
}

void print_formatted_CAN_id(CM_ID_T id) {
	std::cout << std::hex << std::setfill('0') << std::setw(4) << std::uppercase << id << std::dec << " ";
}

std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > filter_edge_sequence(FILE_DATA fd, bool (*predicate)(EDGE_SEQUENCE es)) {
	std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > result;
	//for each msg sequense
	for (auto& msg : fd.msgs) {
		//for each byte in msg data
		for (CM_DATA_SIZE_T i = 0; i < msg.second[0].data.size(); i++) {
			EDGE_SEQUENCE es = get_edges(msg.second, i, 700);

			if (predicate(es))
				result[msg.first].push_back(i);
		}
	}

	return result;
}

std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > filter_byte_sequence(FILE_DATA fd, bool (*predicate)(BYTE_SEQUENCE bs)) {
	std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > result;
	//for each msg sequense
	for (auto& msg : fd.msgs) {
		//for each byte in msg data
		for (CM_DATA_SIZE_T i = 0; i < msg.second[0].data.size(); i++) {
			BYTE_SEQUENCE bs = get_bytes(msg.second, i);

			if (predicate(bs))
				result[msg.first].push_back(i);
		}
	}

	return result;
}

void print_filtered_sequence(std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > id_byte) {
	for (auto& ib : id_byte) {
		print_formatted_CAN_id(ib.first);
		for (auto bn : ib.second)
		{
			std::cout << "  " << (int)bn << " ";
		}
		std::cout << std::endl;
	}
}

bool has_steps(EDGE_SEQUENCE es) {
	if (es.edges.size() == 0 || es.edges.size() > 16)
		return false;

	EDGE_T direction;
	uint8_t seq_counter = 1;
	uint32_t dir_ch_counter = 0;

	auto it = es.edges.begin();
	direction = it->edge;
	it++;

	for (; it != es.edges.end(); it++) {
		if (it->edge == direction) {
			seq_counter++;
		}
		else if (it->edge != direction && seq_counter >= 2) {
			direction = it->edge;
			dir_ch_counter++;
			seq_counter = 1;
		}
		else {
			seq_counter--;
		}
	}

	if (dir_ch_counter >= 1 && seq_counter >= 2)
		return true;

	return false;
}

bool has_pulse(EDGE_SEQUENCE es) {
	if (es.edges.size() == 0 || es.edges.size() > 16)
		return false;

	for (auto it = es.edges.begin(); (it + 1) != es.edges.end(); it++) {
		auto next = (it + 1);
		if (it->edge != next->edge && ((next->timestamp - it->timestamp) < 2000) && it->old_value == next->current_value)
			return true;
	}
	return false;
}

bool is_analog(BYTE_SEQUENCE bs) {

	if (bs.bytes.size() < 100)
		return false;
	if (bs.byte_number >= 6)
		return false;

	int big_change_counter = 0;
	int small_change_counter = 0;
	std::set<CM_BYTE_T> unique_values;
	CM_BYTE_T min_value = bs.bytes[0];
	CM_BYTE_T max_value = bs.bytes[0];

	for (auto it = bs.bytes.begin(); (it + 1) != bs.bytes.end(); it++) {
		unique_values.insert(*it);
		min_value = std::min(min_value, *it);
		max_value = std::max(max_value, *it);
		if (std::abs(*it - *(it + 1)) > 50) {
			big_change_counter++;
		}
		else if (*it != *(it + 1)) {
			small_change_counter++;
		}
	}

	if (big_change_counter > 10 || small_change_counter < 50 || unique_values.size() < 3 || (max_value - min_value < 10))
		return false;

	return true;
}