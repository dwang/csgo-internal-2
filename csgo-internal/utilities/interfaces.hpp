#pragma once

#include <d3d9.h>

#include "singleton.hpp"
#include "../sdk/interfaces/ibaseclientdll.hpp"
#include "../sdk/interfaces/icliententitylist.hpp"
#include "../sdk/interfaces/iclientmode.hpp"
#include "../sdk/interfaces/iinput.hpp"
#include "../sdk/interfaces/iinputsystem.hpp"
#include "../sdk/interfaces/ivengineclient.hpp"
#include "../sdk/interfaces/isurface.hpp"
#include "../sdk/interfaces/ivdebugoverlay.hpp"
#include "../sdk/interfaces/ivmodelrender.hpp"
#include "../sdk/interfaces/ivmodelinfo.hpp"
#include "../sdk/interfaces/irenderview.hpp"
#include "../sdk/interfaces/imaterialsystem.hpp"
#include "../sdk/interfaces/ipanel.hpp"
#include "../sdk/interfaces/cglobalvarsbase.hpp"

class interfaces : public singleton<interfaces>
{
public:
	i_base_client_dll* client;
	i_client_mode* clientmode;
	i_client_entity_list* entity_list;
	iv_engine_client* engine;
	i_surface* surface;
	i_panel* panel;
	iv_debug_overlay* debug_overlay;
	i_input* input;
	i_input_system* input_system;
	iv_model_render* model_render;
	i_render_view* render_view;
	iv_model_info* model_info;
	i_material_system* material_system;
	c_global_vars_base* globals;
	IDirect3DDevice9* direct3d;

	void initialize();

private:
	void* capture_interface(const char* mod, const char* iface);
};
