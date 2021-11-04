#include "UserInputHandler.h"
#include <iostream>
#include <windows.h>

UserInputHandler::UserInputHandler() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 1000 , 1000 });
}

std::vector<std::wstring> UserInputHandler::split(std::wstring str, std::wstring delimiter) {
	std::vector<std::wstring> result;
	while (str.size()) {
		int index = str.find(delimiter);
		if (index != std::wstring::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + delimiter.size());
		}
		else {
			result.push_back(str);
			str = L"";
		}
	}
	return result;
}


std::wstring UserInputHandler::get_user_input(std::wstring request) {
	std::wcout << request + L"> ";
	std::wstring input;
	getline(std::wcin, input);
	return input;
}

USER_CMD UserInputHandler::get_user_command() {
	std::cout << "> ";
	std::wstring input = L"";
	getline(std::wcin, input);

	if (input == L"") return USER_CMD();

	return parse_user_input(input);
}

USER_CMD UserInputHandler::parse_user_input(std::wstring input) {
	USER_CMD result;
	std::wstring arg_name;
	std::wstring arg_value;
	std::vector<std::wstring> tokens = split(input, L" ");
	
	result.cmd = tokens[0];
	for (size_t i = 1; i < tokens.size(); i++)
	{
		if (tokens[i] == L"") continue;

		size_t pos = tokens[i].find('=');
		if (pos != std::wstring::npos) {
			arg_name = tokens[i].substr(0, pos);
			arg_value = tokens[i].substr(pos + 1);
			result.key_value_args[arg_name] = arg_value;
		}
		else {
			arg_value = tokens[i];
			result.plain_args.push_back(arg_value);
		}
	}
	return result;
}





