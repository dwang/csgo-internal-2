#include "../../dependencies/common_includes.hpp"

void hooks::initialize()
{
	clientmode_hook = std::make_unique<vmt_hook>();

	clientmode_hook->setup(interfaces::get().clientmode);

	clientmode_hook->hook(indexes::create_move, create_move);
}

void hooks::restore()
{
	clientmode_hook->release();
}

bool __stdcall hooks::create_move(float frame_time, c_usercmd* user_cmd)
{
	static auto o_create_move = hooks::get().clientmode_hook->original<create_move_fn>(indexes::create_move);
	o_create_move(interfaces::get().clientmode, frame_time, user_cmd);

	if (!user_cmd || !user_cmd->command_number)
		return o_create_move;

	printf("%d\n", user_cmd->tick_count);

	return false;
}
