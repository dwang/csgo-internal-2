#pragma once

#include <map>

#include "singleton.hpp"

class hotkeys : public singleton<hotkeys>
{
	using fn = void(*)();
	std::map<int, fn> functions;

public:
	void add(int key, fn function)
	{
		functions[key] = function;
	}

	void handle(int key)
	{
		if (functions.count(key))
		{
			functions[key]();
		}
	}
};
