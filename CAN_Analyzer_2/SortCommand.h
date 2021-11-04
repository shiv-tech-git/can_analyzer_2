#pragma once
#include "Command.h"

class SortCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};