#include "ErrorCommand.h"

void ErrorCommand::execute(USER_CMD user_cmd) {
	if (user_cmd.cmd != L"") {
		std::cout << "WRONG COMMAND" << std::endl;
	}
}