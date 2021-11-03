#pragma once
#include <string>
#include <vector>
#include "CMA_Types.h"

class UserInputHandler {
public:
	UserInputHandler();
	USER_CMD get_user_command();
	std::string get_user_input(std::string request);

private:
	USER_CMD parse_user_input(std::string input);
	std::vector<std::string> split(std::string str, std::string delimiter);
};