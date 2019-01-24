#pragma once

#include "../common_includes.hpp"

class globals : public singleton<globals>
{
public:
	HWND window;
	std::array<bool, 256> pressed;
	bool d3d_init;
	bool unload;
};
