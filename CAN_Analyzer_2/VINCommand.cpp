#include "VINCommand.h"
#include "CMA_Utils.h"
#include "FileReader.h"
#include "CMA_State.h"

#include <unordered_map>

void VINCommand::execute(USER_CMD user_cmd) {
	if (user_cmd.plain_args.size() == 0 && CMA_State::instance().get_current_file_absolute_path() == L"") {
		std::cout << "Enter file name or directory as first argument" << std::endl;
		return;
	}

	std::vector<FILE_DATA> files;
	FileReader fr;
	if (!user_cmd.plain_args.size() == 0) {
		std::wstring arg1 = user_cmd.plain_args[0];
		if (is_relative_file_name(arg1)) {
			std::wstring cd = CMA_State::instance().get_current_directory();
			std::wstring afp = cd + L'\\' + arg1;
			if (!file_exists(afp)) {
				std::wcout << L"There is no file \'" + arg1 + L"\' in " + cd << std::endl;
				return;
			}
			else {
				files.push_back(fr.parse_log_file(afp));
			}
		}
		else if (is_absolute_file_name(arg1)) {
			if (!file_exists(arg1)) {
				std::wcout << L"File '" + arg1 + L"' does not exist" << std::endl;
				return;
			}
			else {
				files.push_back(fr.parse_log_file(arg1));
			}
		}
		else if (is_directory(arg1)) {
			if (!directory_exists(arg1)) {
				std::wcout << L"Directory '" + arg1 + L"' does not exists" << std::endl;
				return;
			}
			else {
				std::vector<std::wstring> file_names = get_file_names_from_directory(arg1);
				for (auto file_name : file_names) {
					files.push_back(fr.parse_log_file(file_name));
				}
			}
		}
	}
	else {
		std::wstring afn = CMA_State::instance().get_current_file_absolute_path();
		files.push_back(fr.parse_log_file(afn));
	}


	for (auto file : files) {
		std::unordered_map<CM_ID_T, CM_DATA_T> file_result;

		for (auto msg_seq_it = file.msgs.begin(); msg_seq_it != file.msgs.end(); msg_seq_it++) {
			CM_ID_T id = msg_seq_it->first;

			for (auto msg_it = msg_seq_it->second.begin(); msg_it != msg_seq_it->second.end(); msg_it++) {
				if (is_VIN_part(msg_it->data)) {
					file_result[id] = msg_it->data;
					break;
				}
			}
		}
		if (file_result.size() > 0) {
			std::wcout << file.name << std::endl;
			for (auto vin_msg : file_result) {
				std::cout << std::hex << std::setfill('0') << std::setw(4) << std::uppercase << vin_msg.first << std::dec << " ";
				for (auto b : vin_msg.second) {
					std::cout << b;
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

	}
}