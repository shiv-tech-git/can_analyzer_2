#pragma once
#include "CMA_Types.h"
#include "Command.h"
#include <unordered_map>

class CommandProcessor {
public:
	void add_cmd_handler(std::wstring cmd_name, Command* cmd_handler);
	void handle_cmd(USER_CMD user_cmd);
	void init_handlers();

private:
	std::unordered_map<std::wstring, Command*> handlers;
};