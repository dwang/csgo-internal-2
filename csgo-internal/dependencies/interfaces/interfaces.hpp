#pragma once

#include "ibaseclientdll.hpp"
#include "icliententitylist.hpp"
#include "iclientmode.hpp"
#include "ivengineclient.hpp"
#include "isurface.hpp"
#include "ipanel.hpp"

class interfaces : public singleton<interfaces>
{
public:
	i_base_client_dll* client;
	i_client_mode* clientmode;
	i_client_entity_list* entity_list;
	iv_engine_client* engine;
	i_surface* surface;
	i_panel* panel;
	IDirect3DDevice9* direct3d;

	void initialize();

private:
	void* capture_interface(const char* mod, const char* iface);
};
