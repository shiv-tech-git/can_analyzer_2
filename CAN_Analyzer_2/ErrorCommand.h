#pragma once
#include "Command.h"

class ErrorCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};