#pragma once

#include <map>

#include "../../utilities/singleton.hpp"
#include "../../utilities/render.hpp"

class menu : public singleton<menu>
{
private:
	size_t active_tab;
	std::map<std::string, void(*)()> render_tab;

public:
	ImGuiStyle style;
	bool opened;
	
	void initialize();
	void render();
};
