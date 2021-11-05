#pragma once
#include "Command.h"

class PulseCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};