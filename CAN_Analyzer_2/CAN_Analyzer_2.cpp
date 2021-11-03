#include "UserInputHandler.h"
#include "CommandProcessor.h"

int main()
{
	CommandProcessor cp;
	UserInputHandler uih;

	cp.init_handlers();

	while (true) cp.handle_cmd(uih.get_user_command());

    return 0;
}
