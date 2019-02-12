#pragma once

#include <map>

#include "../../dependencies/utilities/render.hpp"
#include "../../dependencies/utilities/singleton.hpp"

class menu : public singleton<menu>
{
private:
	size_t active_tab;
	std::map<std::string, void(*)()> render_tab;

public:
	bool opened;
	ImGuiStyle style;
	void initialize();
	void render();
};
