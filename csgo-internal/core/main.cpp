#define VC_EXTRALEAN
#include <Windows.h>
#include <fstream>
#include <thread>

#include "../utilities/utilities.hpp"
#include "../utilities/interfaces.hpp"
#include "../utilities/netvars.hpp"
#include "../utilities/globals.hpp"
#include "../utilities/hotkeys.hpp"
#include "../core/hooks/hooks.hpp"

unsigned long __stdcall on_dll_attach(void* reserved)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif

	utilities::get().get_handle_safe("serverbrowser.dll");
	interfaces::get().initialize();
	netvar_manager::get().initialize(interfaces::get().client->get_client_classes());
	netvar_manager::get().dump_netvars(interfaces::get().client->get_client_classes());
	hooks::get().initialize();

	hotkeys::get().add(VK_INSERT, []() { menu::get().opened = !menu::get().opened; });
	hotkeys::get().add(VK_END, []() { globals::get().unload = true; });

	while (!globals::get().unload)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(reserved), 0);
	return 0ul;
}

void __stdcall on_dll_detach()
{
#ifdef _DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();
#endif
}

bool __stdcall DllMain(void* instance, unsigned long reason_to_call, void* reserved)
{
	if (reason_to_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(reinterpret_cast<HMODULE>(instance));
		auto h = CreateThread(0, 0, on_dll_attach, instance, 0, 0);
		CloseHandle(h);
	}
	else if (reason_to_call == DLL_PROCESS_DETACH)
	{
		if (!reserved)
		{
			hooks::get().restore();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		on_dll_detach();
	}

	return true;
}
