#pragma once

#include "../utilities/utilities.hpp"

class i_input_system
{
public:
	void enable_input(bool enable)
	{
		return utilities::get().call_vfunc<11, void>(this, enable);
	}

	void reset_input_state()
	{
		return utilities::get().call_vfunc<39, void>(this);
	}
};
