#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

#include "../utilities/singleton.hpp"

#define M_PI 3.14159265358979323846

class utilities : public singleton<utilities>
{
public:
	std::uint8_t* pattern_scan(void* module, const char* signature);
	HMODULE get_handle_safe(std::string handle);
	std::string format(const char *fmt, ...);
};
