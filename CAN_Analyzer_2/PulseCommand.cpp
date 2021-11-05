#include "PulseCommand.h"
#include <map>

void PulseCommand::execute(USER_CMD user_cmd) {
	std::wstring file_name = CMA_State::instance().get_current_file_absolute_path();
	if (file_name == L"") {
		std::cout << "File is undefined" << std::endl;
		return;
	}

	FileReader fr;
	FILE_DATA fd = fr.parse_log_file(file_name);

	std::map<CM_ID_T, std::vector<CM_DATA_SIZE_T> > result;
	result = filter_edge_sequence(fd, has_pulse);
	print_filtered_sequence(result);
}
