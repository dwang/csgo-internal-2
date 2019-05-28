#pragma once

#include <array>

#include "singleton.hpp"
#include "../sdk/classes/entity.hpp"

class globals : public singleton<globals>
{
public:
	player_t* local_player;
	HWND window;
	std::array<bool, 256> pressed;
	bool d3d_init;
	bool unload;
};
