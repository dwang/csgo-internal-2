#pragma once

#include "../../dependencies/common_includes.hpp"

class menu : public singleton<menu>
{
private:
	size_t active_tab;
	std::map<std::string, void(*)()> render_tab;

public:
	bool opened;
	ImGuiStyle style;
	void initialize(IDirect3DDevice9* device);
	void render();
};
