#include "bunnyhop.hpp"

#include "../../dependencies/utilities/globals.hpp"
#include "../../sdk/sdk.hpp"

void bunnyhop::create_move(c_usercmd* user_cmd)
{
	static bool last_jumped = false;
	static bool should_fake = false;

	if (!last_jumped && should_fake)
	{
		should_fake = false;
		user_cmd->buttons |= in_jump;
	}
	else if (user_cmd->buttons & in_jump)
	{
		if (globals::get().local_player->flags() & fl_onground)
		{
			last_jumped = true;
			should_fake = true;
		}
		else
		{
			user_cmd->buttons &= ~in_jump;
			last_jumped = false;
		}
	}
	else
	{
		last_jumped = false;
		should_fake = false;
	}
}
