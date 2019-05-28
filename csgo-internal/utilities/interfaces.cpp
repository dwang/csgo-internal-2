#include "interfaces.hpp"

#include <Windows.h>
#include "utilities.hpp"

void* interfaces::capture_interface(const char* mod, const char* iface)
{
	using fn_capture_iface_t = void*(*)(const char*, int*);
	auto fn_addr = reinterpret_cast<fn_capture_iface_t>(GetProcAddress(GetModuleHandleA(mod), "CreateInterface"));

	auto iface_addr = fn_addr(iface, nullptr);
	printf("found %s at 0x%p\n", iface, fn_addr(iface, nullptr));

	return iface_addr;
}

void interfaces::initialize()
{
	client = reinterpret_cast<i_base_client_dll*>(capture_interface("client_panorama.dll", "VClient018"));
	clientmode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<std::uintptr_t**>(client))[10] + 5);
	entity_list = reinterpret_cast<i_client_entity_list*>(capture_interface("client_panorama.dll", "VClientEntityList003"));
	engine = reinterpret_cast<iv_engine_client*>(capture_interface("engine.dll", "VEngineClient014"));
	surface = reinterpret_cast<i_surface*>(capture_interface("vguimatsurface.dll", "VGUI_Surface031"));
	panel = reinterpret_cast<i_panel*>(capture_interface("vgui2.dll", "VGUI_Panel009"));
	debug_overlay = reinterpret_cast<iv_debug_overlay*>(capture_interface("engine.dll", "VDebugOverlay004"));
	input_system = reinterpret_cast<i_input_system*>(capture_interface("inputsystem.dll", "InputSystemVersion001"));
	model_render = reinterpret_cast<iv_model_render*>(capture_interface("engine.dll", "VEngineModel016"));
	model_info = reinterpret_cast<iv_model_info*>(capture_interface("engine.dll", "VModelInfoClient004"));
	render_view = reinterpret_cast<i_render_view*>(capture_interface("engine.dll", "VEngineRenderView014"));
	material_system = reinterpret_cast<i_material_system*>(capture_interface("materialsystem.dll", "VMaterialSystem080"));

	direct3d = **reinterpret_cast<IDirect3DDevice9***>(utilities::get().pattern_scan(GetModuleHandleA("shaderapidx9.dll"), "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	input = *reinterpret_cast<i_input**>(utilities::get().pattern_scan(GetModuleHandleA("client_panorama.dll"), "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
	globals = **reinterpret_cast<c_global_vars_base***>((*reinterpret_cast<std::uintptr_t**>(client)[0] + 27));
}
