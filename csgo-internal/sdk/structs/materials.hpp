#pragma once

#include "../../dependencies/utilities/utilities.hpp"

using material_handle_t = unsigned short;
class i_material
{
public:
	const char* get_name()
	{
		return utilities::get().call_vfunc<0, const char*>(this);
	}

	const char* get_group_name()
	{
		return utilities::get().call_vfunc<1, const char*>(this);
	}

	void set_alpha(float alpha)
	{
		return utilities::get().call_vfunc<27, void>(this, alpha);
	}

	void set_alpha(int alpha)
	{
		return utilities::get().call_vfunc<27, void>(this, static_cast<float>(alpha) / 255.f);
	}

	void set_color(float r, float g, float b)
	{
		return utilities::get().call_vfunc<28, void>(this, r, g, b);
	}

	void set_color(int r, int g, int b)
	{
		return utilities::get().call_vfunc<28, void>(this, static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f);
	}

	void set_color(int color32)
	{
		int r1 = (color32 >> 16) & 0xff;
		int g1 = (color32 >> 8) & 0xff;
		int b1 = color32 & 0xff;

		set_color(r1, g1, b1);
	}

	void set_flag(int flag, bool on)
	{
		return utilities::get().call_vfunc<29, void>(this, flag, on);
	}
};