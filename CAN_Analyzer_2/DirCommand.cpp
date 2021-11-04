#include "DirCommand.h"
#include "CMA_Utils.h"
#include "CMA_State.h"

void DirCommand::execute(USER_CMD user_cmd) {
	if (user_cmd.plain_args.size() == 0) {
		std::cout << "Enter directory to set it as word directory" << std::endl;
		return;
	}

	if (user_cmd.plain_args[0] == L"-s") {
		std::wstring c_dir = CMA_State::instance().get_current_directory();
		if (c_dir == L"") {
			std::cout << "Current directory is undefined" << std::endl;
			return;
		}
		else {
			std::wcout << c_dir << std::endl;
			return;
		}
	}

	std::wstring dir = user_cmd.plain_args[0];
	if (!is_directory(dir)) {
		std::cout << "Entered string is not a valie directory" << std::endl;
		return;
	}
	else if (!directory_exists(dir)) {
		std::cout << "Directory does not exits in file system" << std::endl;
	}
	else {
		CMA_State::instance().set_current_directory(dir);
	}
}