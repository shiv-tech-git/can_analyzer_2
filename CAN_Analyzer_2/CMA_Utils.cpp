#include "CMA_Utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <locale>
#include <codecvt>

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

EDGE_SEQUENCE get_edges(std::vector<CAN_MSG>& msgs, CM_DATA_SIZE_T byte_number) {
	EDGE_SEQUENCE result;
	result.id = msgs[0].id;
	result.byte_number = byte_number;

	auto it = msgs.begin();
	auto last = it;
	it++;
	for (; it != msgs.end(); it++) {
		if (it->data[byte_number] != last->data[byte_number] && std::abs((int)(it->timestamp - last->timestamp)) > EDGE_CHANGE_DELAY_MS) {
			if (it->data[byte_number] > last->data[byte_number]) {
				result.edges.push_back({ leading, it->timestamp });
			}
			else {
				result.edges.push_back({ trailing, it->timestamp });
			}
			last = it;
		}
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

