#include "VINCommand.h"
#include <iostream>
#include "CMA_Utils.h"
#include "FileReader.h"

#include <unordered_map>

void VINCommand::execute(USER_CMD user_cmd) {
	if (user_cmd.plain_args.size() == 0) {
		std::cout << "Enter file name or directory as first argument" << std::endl;
		return;
	}

	std::string arg1 = user_cmd.plain_args[0];

	if (is_relative_file_name(arg1)) {
		std::cout << "Relative path is unsupported now." << std::endl;
		return;
	}

	std::vector<FILE_DATA> files;
	FileReader fr;

	if (is_absolute_file_name(arg1)) {
		files.push_back(fr.parse_log_file(arg1));
	}

	if (is_directory(arg1)) {
		std::vector<std::string> file_names = get_file_names_from_directory(arg1);
		for (auto file_name : file_names) {
			files.push_back(fr.parse_log_file(file_name));
		}
	}

	int test = 1;
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
			std::cout << file.name << std::endl;
			for (auto vin_msg : file_result) {
				std::cout << vin_msg.first << " ";
				for (auto b : vin_msg.second) {
					std::cout << b;
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

	}
}