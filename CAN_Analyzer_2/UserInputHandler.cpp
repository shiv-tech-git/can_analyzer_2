#include "UserInputHandler.h"
#include <iostream>
#include <windows.h>

UserInputHandler::UserInputHandler() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
}

std::vector<std::string> UserInputHandler::split(std::string str, std::string delimiter) {
	std::vector<std::string> result;
	while (str.size()) {
		int index = str.find(delimiter);
		if (index != std::string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + delimiter.size());
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}


std::string UserInputHandler::get_user_input(std::string request) {
	std::cout << request + "> ";
	std::string result;
	std::getline(std::cin, result);
	return result;
}

USER_CMD UserInputHandler::get_user_command() {
	std::cout << "> ";
	std::string input;
	std::getline(std::cin, input);

	if (input == "") return USER_CMD();

	return parse_user_input(input);
}

USER_CMD UserInputHandler::parse_user_input(std::string input) {
	USER_CMD result;
	std::vector<std::string> tokens = split(input, " ");
	
	result.cmd = tokens[0];
	for (size_t i = 1; i < tokens.size(); i++)
	{
		if (tokens[i] == "") continue;

		size_t pos = tokens[i].find('=');
		if (pos != std::string::npos) {
			result.key_value_args.push_back({ tokens[i] .substr(0, pos), tokens[i].substr(pos + 1) });
		}
		else {
			result.plain_args.push_back(tokens[i]);
		}
	}
	return result;
}





