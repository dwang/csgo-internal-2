#include "../../dependencies/common_includes.hpp"

void bunnyhop::create_move(c_usercmd* user_cmd)
{
	static bool last_jumped = false;
	static bool should_fake = false;

	auto local_player = reinterpret_cast<player_t*>(interfaces::get().entity_list->get_client_entity(interfaces::get().engine->get_local_player()));

	if (!last_jumped && should_fake)
	{
		should_fake = false;
		user_cmd->buttons |= in_jump;
	}
	else if (user_cmd->buttons & in_jump)
	{
		if (local_player->flags() & fl_onground)
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
