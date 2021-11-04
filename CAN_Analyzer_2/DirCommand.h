#pragma once
#include "Command.h"

class DirCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};