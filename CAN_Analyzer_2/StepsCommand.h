#pragma once
#include "Command.h"

class StepsCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};