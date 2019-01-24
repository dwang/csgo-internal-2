#pragma once

#include "../../dependencies/common_includes.hpp"

class settings : public singleton<settings>
{
public:
	struct aimbot
	{
		bool enabled;
	} aimbot;

	struct visuals
	{
		bool watermark;
	} visuals;

	struct misc
	{
		bool bunnyhop;
	} misc;
};