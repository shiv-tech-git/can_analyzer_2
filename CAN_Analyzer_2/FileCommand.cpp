#include "FileCommand.h"

void FileCommand::execute(USER_CMD user_cmd) {
	if (user_cmd.plain_args.size() == 0) {
		std::cout << "Enter file name to set it as current file" << std::endl;
		return;
	}

	if (user_cmd.plain_args[0] == L"-s") {
		std::wstring cfn = CMA_State::instance().get_current_file_name();
		std::wstring cfap = CMA_State::instance().get_current_file_absolute_path();
		if (cfn == L"" && cfap == L"") {
			std::wcout << "Current file is undefined" << std::endl;
		}
		else if (cfn != L"") {
			std::wcout << cfn << std::endl;
		}
		else if (cfap != L"") {
			std::wcout << get_file_name_from_absolute_path(cfap) << std::endl;
		}
		return;
	}

	if (user_cmd.plain_args[0] == L"-sa") {
		std::wstring cfn = CMA_State::instance().get_current_file_name();
		std::wstring cfap = CMA_State::instance().get_current_file_absolute_path();
		std::wstring cd = CMA_State::instance().get_current_directory();
		if (cfap != L"") {
			std::wcout << cfap << std::endl;
		}
		else if (cd != L"" && cfn != L"") {
			std::wcout << cd + L'\\' + cfn << std::endl;
		}
		else {
			std::cout << "Current file is undefined" << std::endl;
		}
		return;
	}

	std::wstring file_name = user_cmd.plain_args[0];
	if (is_relative_file_name(file_name)) {
		if (CMA_State::instance().get_current_directory() == L"") {
			std::cout << "You need to enter absolute file name or set working directory" << std::endl;
		}
		else {
			std::wstring cd = CMA_State::instance().get_current_directory();
			if (!file_exists(cd + L'\\' + file_name)) {
				std::wcout << L"There is no file \'" + file_name + L"\' in " + cd << std::endl;
			}
			else {
				CMA_State::instance().set_current_file_name(file_name);
			}
		}

	}
	else if (is_absolute_file_name(file_name))
	{
		if (!file_exists(file_name)) {
			std::cout << "File does not exist in file system" << std::endl;
		}
		else {
			CMA_State::instance().set_current_file_absolute_path(file_name);
		}
	}
	else
	{
		std::cout << "Invalid file name" << std::endl;
	}
	return;
}