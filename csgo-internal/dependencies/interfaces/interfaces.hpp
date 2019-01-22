#pragma once

#include "ibaseclientdll.hpp"
#include "iclientmode.hpp"

class interfaces : public singleton<interfaces>
{
public:
	i_base_client_dll* client;
	i_client_mode* clientmode;

	void initialize();
private:
	void* capture_interface(const char* mod, const char* iface);
};
