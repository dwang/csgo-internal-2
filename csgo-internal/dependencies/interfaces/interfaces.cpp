#include "../common_includes.hpp"

void* interfaces::capture_interface(const char* mod, const char* iface)
{
	using fn_capture_iface_t = void*(*)(const char*, int*);
	auto fn_addr = (fn_capture_iface_t)GetProcAddress(GetModuleHandleA(mod), "CreateInterface");

	auto iface_addr = fn_addr(iface, nullptr);
	printf("found %s at 0x%p\n", iface, fn_addr(iface, nullptr));

	return iface_addr;
}

void interfaces::initialize()
{
	client = reinterpret_cast<i_base_client_dll*>(capture_interface("client_panorama.dll", "VClient018"));
	clientmode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);
}
