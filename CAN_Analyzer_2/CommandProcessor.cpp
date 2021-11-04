#include "CommandProcessor.h"

#include "ErrorCommand.h"
#include "ExitCommand.h"
#include "VINCommand.h"
#include "DirCommand.h"
#include "FileCommand.h"

void CommandProcessor::add_cmd_handler(std::wstring cmd_name, Command* cmd_handler) {
	handlers[cmd_name] = cmd_handler;
}

void CommandProcessor::handle_cmd(USER_CMD user_cmd) {
	if (handlers.find(user_cmd.cmd) != handlers.end()) {
		handlers[user_cmd.cmd]->execute(user_cmd);
		return;
	}
	else {
		ErrorCommand ec;
		ec.execute(user_cmd);
	}
}

void CommandProcessor::init_handlers() {
	add_cmd_handler(L"exit", new ExitCommand());
	add_cmd_handler(L"vin", new VINCommand());
	add_cmd_handler(L"file", new FileCommand());
	add_cmd_handler(L"dir", new DirCommand());
}