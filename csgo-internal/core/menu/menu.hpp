#pragma once

#include <map>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "../../dependencies/utilities/singleton.hpp"

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
