#pragma once

class i_render_view
{
public:
	const void set_color_modulation(float r, float g, float b)
	{
		using original_fn = const void(__thiscall*)(i_render_view*, float*);
		float clr[3] = { r, g, b };
		return (*(original_fn**)this)[6](this, clr);
	}

	const void alpha_modulate(float blend)
	{
		using original_fn = const void(__thiscall*)(i_render_view*, float);
		return (*(original_fn**)this)[4](this, blend);
	}
};

