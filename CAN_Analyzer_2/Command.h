#pragma once
#include "CMA_Types.h"

class Command {
public:
	virtual void execute(USER_CMD user_cmd) = 0;
};