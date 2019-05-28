#pragma once

#include "../utilities/utilities.hpp"

class i_panel
{
public:
	const char* get_panel_name(unsigned int panel_id)
	{
		return utilities::get().call_vfunc<36, const char*>(this, panel_id);
	}
};
