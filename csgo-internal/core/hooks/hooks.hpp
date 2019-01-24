#pragma once

#include "../../dependencies/common_includes.hpp"

namespace indexes
{
	constexpr auto create_move = 24;
	constexpr auto paint_traverse = 41;
	constexpr auto end_scene = 42;
	constexpr auto reset = 16;
}

class hooks : public singleton<hooks>
{
public:
	void initialize();
	void restore();

	std::unique_ptr<vmt_hook> clientmode_hook;
	std::unique_ptr<vmt_hook> panel_hook;
	std::unique_ptr<vmt_hook> direct3d_hook;

	WNDPROC original_wndproc;

	using create_move_fn = bool(__thiscall*)(i_client_mode*, float, c_usercmd*);
	using paint_traverse_fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
	using end_scene_fn = long(__stdcall*)(IDirect3DDevice9*);
	using reset_fn = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

	static bool __stdcall create_move(float frame_time, c_usercmd* user_cmd);
	static void __stdcall paint_traverse(unsigned int panel, bool force_repaint, bool allow_force);
	static long __stdcall end_scene(IDirect3DDevice9* device);
	static long __stdcall reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters);
	static LRESULT __stdcall wndproc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
};
