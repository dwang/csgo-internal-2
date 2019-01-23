#pragma once

#include "ibaseclientdll.hpp"
#include "icliententitylist.hpp"
#include "iclientmode.hpp"
#include "ivengineclient.hpp"

class interfaces : public singleton<interfaces>
{
public:
	i_base_client_dll* client;
	i_client_mode* clientmode;
	i_client_entity_list* entity_list;
	iv_engine_client* engine;

	void initialize();

private:
	void* capture_interface(const char* mod, const char* iface);
};
