#pragma once
#include <string>
#include <vector>
#include "CMA_Types.h"

class UserInputHandler {
public:
	UserInputHandler();
	USER_CMD get_user_command();
	std::wstring get_user_input(std::wstring request);

private:
	USER_CMD parse_user_input(std::wstring input);
	std::vector<std::wstring> split(std::wstring str, std::wstring delimiter);
};