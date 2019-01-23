#pragma once

#include "../../dependencies/utilities/singleton.hpp"
#include "../../sdk/classes/c_usercmd.hpp"

class bunnyhop : public singleton<bunnyhop>
{
public:
	void create_move(c_usercmd* user_cmd);
};
