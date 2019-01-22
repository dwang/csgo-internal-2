#include "../dependencies/common_includes.hpp"

unsigned long __stdcall on_dll_attach(void* reserved)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif

	interfaces::get().initialize();
	hooks::get().initialize();

	while (!GetAsyncKeyState(VK_END))
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
