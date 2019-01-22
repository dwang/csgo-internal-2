#pragma once

#include "../utilities/singleton.hpp"

#define M_PI 3.14159265358979323846

class utilities : public singleton<utilities>
{
	std::uint8_t* pattern_scan(void* module, const char* signature);
};
