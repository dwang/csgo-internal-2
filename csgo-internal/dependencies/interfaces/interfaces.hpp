#pragma once

#include <d3d9.h>

#include "../utilities/singleton.hpp"

#include "ibaseclientdll.hpp"
#include "icliententitylist.hpp"
#include "iclientmode.hpp"
#include "iinput.hpp"
#include "iinputsystem.hpp"
#include "ivengineclient.hpp"
#include "isurface.hpp"
#include "ivdebugoverlay.hpp"
#include "ivmodelrender.hpp"
#include "ivmodelinfo.hpp"
#include "irenderview.hpp"
#include "imaterialsystem.hpp"
#include "ipanel.hpp"
#include "cglobalvarsbase.hpp"

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
