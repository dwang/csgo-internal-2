#pragma once

#include "../../utilities/utilities.hpp"
#include "../../sdk/misc/vector.hpp"

class iv_debug_overlay
{
public:
	bool world_to_screen(const vec3_t& in, vec3_t& out)
	{
		return static_cast<bool>(utilities::get().call_vfunc<13, int>(this, &in, &out) != 1);
	}
};
