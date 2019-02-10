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
		bool box_esp;
		bool name_esp;
		bool chams;
		bool chams_ignore_z;
		bool watermark;
	} visuals;

	struct misc
	{
		bool bunnyhop;
	} misc;
};
