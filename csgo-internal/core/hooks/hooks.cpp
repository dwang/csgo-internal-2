#include "../../dependencies/common_includes.hpp"

void hooks::initialize()
{
	clientmode_hook = std::make_unique<vmt_hook>();
	panel_hook = std::make_unique<vmt_hook>();
	direct3d_hook = std::make_unique<vmt_hook>();

	clientmode_hook->setup(interfaces::get().clientmode);
	panel_hook->setup(interfaces::get().panel);
	direct3d_hook->setup(interfaces::get().direct3d);

	clientmode_hook->hook(indexes::create_move, create_move);
	panel_hook->hook(indexes::paint_traverse, paint_traverse);
	direct3d_hook->hook(indexes::end_scene, end_scene);
	direct3d_hook->hook(indexes::reset, reset);

	globals::get().window = FindWindowA("Valve001", nullptr);
	original_wndproc = (WNDPROC)SetWindowLongPtrA(globals::get().window, GWL_WNDPROC, (LONG)wndproc);

	render::get().setup_fonts();
}

void hooks::restore()
{
	interfaces::get().input->m_mouse_initiated = true;
	interfaces::get().input->m_mouse_active = true;
	interfaces::get().input_system->enable_input(true);

	clientmode_hook->release();
	panel_hook->release();
	direct3d_hook->release();

	SetWindowLongPtrA(globals::get().window, GWL_WNDPROC, (LONG)hooks::get().original_wndproc);
}

bool __stdcall hooks::create_move(float frame_time, c_usercmd* user_cmd)
{
	static auto o_create_move = hooks::get().clientmode_hook->original<create_move_fn>(indexes::create_move);
	o_create_move(interfaces::get().clientmode, frame_time, user_cmd);

	if (!user_cmd || !user_cmd->command_number)
		return o_create_move;

	if (!interfaces::get().entity_list->get_client_entity(interfaces::get().engine->get_local_player()))
		return o_create_move;

	if (settings::get().misc.bunnyhop)
		bunnyhop::get().create_move(user_cmd);

	return false;
}

void __stdcall hooks::paint_traverse(unsigned int panel, bool force_repaint, bool allow_force)
{
	static auto o_paint_traverse = hooks::get().panel_hook->original<paint_traverse_fn>(indexes::paint_traverse);

	std::string panel_name = interfaces::get().panel->get_panel_name(panel);

	o_paint_traverse(interfaces::get().panel, panel, force_repaint, allow_force);

	static unsigned int _panel = 0;
	static bool once = false;

	if (!once)
	{
		PCHAR panel_char = (PCHAR)interfaces::get().panel->get_panel_name(panel);
		if (strstr(panel_char, "MatSystemTopPanel"))
		{
			_panel = panel;
			once = true;
		}
	}
	else if (_panel == panel)
	{
		if (settings::get().visuals.watermark)
			render::get().draw_text(1, 1, render::get().watermark_font, "csgo-internal - " __DATE__, false, color(255, 255, 255));
	}
}

long __stdcall hooks::end_scene(IDirect3DDevice9* device)
{
	static auto o_end_scene = hooks::get().direct3d_hook->original<end_scene_fn>(indexes::end_scene);

	if (!globals::get().d3d_init)
	{
		menu::get().initialize(device);
		globals::get().d3d_init = true;
	}

	ImGui::GetIO().MouseDrawCursor = menu::get().opened;
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	interfaces::get().input->m_mouse_initiated = !menu::get().opened;

	if (!interfaces::get().input->m_mouse_initiated)
	{
		interfaces::get().input->m_mouse_active = false;
		interfaces::get().input_system->enable_input(false);
		interfaces::get().input_system->reset_input_state();
	}
	else
		interfaces::get().input_system->enable_input(true);

	if (menu::get().opened)
		menu::get().render();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return o_end_scene(device);
}

long __stdcall hooks::reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters)
{
	static auto o_reset = hooks::get().direct3d_hook->original<reset_fn>(indexes::reset);

	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto hr = o_reset(device, presentation_parameters);
	ImGui_ImplDX9_CreateDeviceObjects();

	return hr;
}

extern IMGUI_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall hooks::wndproc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		globals::get().pressed[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		globals::get().pressed[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		globals::get().pressed[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		globals::get().pressed[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		globals::get().pressed[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		globals::get().pressed[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	{
		auto button = GET_XBUTTON_WPARAM(wparam);
		if (button == XBUTTON1)
		{
			globals::get().pressed[VK_XBUTTON1] = (message == WM_XBUTTONDOWN);
		}
		else if (button == XBUTTON2)
		{
			globals::get().pressed[VK_XBUTTON2] = (message == WM_XBUTTONDOWN);
		}
	}
		break;
	case WM_KEYDOWN:
		globals::get().pressed[wparam] = true;
		break;
	case WM_KEYUP:
		globals::get().pressed[wparam] = false;
		hotkeys::get().handle(wparam);
		break;
	default:
		break;
	}

	if (menu::get().opened && ImGui_ImplWin32_WndProcHandler(window, message, wparam, lparam))
		return true;

	return CallWindowProc(hooks::get().original_wndproc, window, message, wparam, lparam);
}
