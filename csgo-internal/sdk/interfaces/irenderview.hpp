#pragma once

#include "../utilities/utilities.hpp"

class i_render_view
{
public:
	const void set_color_modulation(float r, float g, float b)
	{
		float clr[3] = { r, g, b };
		return utilities::get().call_vfunc<6, const void>(this, clr);
	}

	const void alpha_modulate(float blend)
	{
		return utilities::get().call_vfunc<4, const void>(this, blend);
	}
};
