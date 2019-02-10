#pragma once

#include "../../dependencies/utilities/singleton.hpp"

class settings : public singleton<settings>
{
public:
	struct aimbot
	{
		bool enabled;
	} aimbot;

	struct visuals
	{
		int esp_mode = 2;
		bool box_esp = true;
		bool name_esp = true;
		bool chams = true;
		bool chams_ignore_z = false;
		bool watermark = true;
	} visuals;

	struct misc
	{
		bool bunnyhop = true;
	} misc;
};
