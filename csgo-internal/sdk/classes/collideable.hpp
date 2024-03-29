#pragma once

#include "../../utilities/utilities.hpp"
#include "../misc/vector.hpp"

class collideable_t
{
public:
	vec3_t& mins()
	{
		return utilities::get().call_vfunc<1, vec3_t&>(this);
	}

	vec3_t& maxs()
	{
		return utilities::get().call_vfunc<2, vec3_t&>(this);
	}
};
