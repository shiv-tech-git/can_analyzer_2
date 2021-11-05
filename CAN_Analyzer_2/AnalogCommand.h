#pragma once
#include "Command.h"

class AnalogCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};