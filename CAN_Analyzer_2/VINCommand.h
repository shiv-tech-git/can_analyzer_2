#pragma once
#include "Command.h"

class VINCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};