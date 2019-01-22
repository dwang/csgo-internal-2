#pragma once

#include "../../dependencies/common_includes.hpp"

namespace indexes
{
	constexpr auto create_move = 24;
}

class hooks : public singleton<hooks>
{
public:
	void initialize();
	void restore();

	std::unique_ptr<vmt_hook> clientmode_hook;

	using create_move_fn = bool(__thiscall*)(i_client_mode*, float, c_usercmd*);

	static bool __stdcall create_move(float frame_time, c_usercmd* user_cmd);
};
