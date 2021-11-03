#pragma once
#include "Command.h"

class ExitCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};