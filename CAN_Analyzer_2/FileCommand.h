#pragma once
#include "Command.h"

class FileCommand : public Command {
public:
	void execute(USER_CMD user_cmd) override;
};