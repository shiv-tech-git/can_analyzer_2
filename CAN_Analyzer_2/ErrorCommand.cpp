#include "ErrorCommand.h"
#include <iostream>

void ErrorCommand::execute(USER_CMD user_cmd) {
	if (user_cmd.cmd != "") {
		std::cout << "WRONG COMMAND" << std::endl;
	}
}