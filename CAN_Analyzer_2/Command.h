#pragma once
#include "CMA_Types.h"
#include "CMA_State.h"
#include "CMA_Utils.h"
#include "FileReader.h"
#include <iostream>

class Command {
public:
	virtual void execute(USER_CMD user_cmd) = 0;
};