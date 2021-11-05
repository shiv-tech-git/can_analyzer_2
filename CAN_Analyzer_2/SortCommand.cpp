#include "SortCommand.h"
#include <map>

void SortCommand::execute(USER_CMD user_cmd) {
	std::wstring file_name = CMA_State::instance().get_current_file_absolute_path();
	if (file_name == L"") {
		std::cout << "File is undefined" << std::endl;
		return;
	}
	
	FileReader fr;
	FILE_DATA fd = fr.parse_log_file(file_name);
	std::map<CM_ID_T, uint32_t> id_count;
	for (auto msg : fd.msgs) {
		CM_ID_T id = msg.first;
		size_t s = msg.second.size();
		id_count[s] = id;
	}

	for (auto msg : id_count) {
		print_formatted_CAN_id(msg.second);
		std::cout <<" " << msg.first << std::endl;
	}
	return;
}