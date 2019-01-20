#include "../dependencies/common_includes.hpp"

unsigned long __stdcall on_dll_attach(void* reserved)
{
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(reserved), 0);
	return 0ul;
}

void __stdcall on_dll_detach()
{
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();
}

bool __stdcall DllMain(void* instance, unsigned long reason_to_call, void* reserved)
{
	if (reason_to_call == DLL_PROCESS_ATTACH)
	{
		auto h = CreateThread(0, 0, on_dll_attach, instance, 0, 0);
		CloseHandle(h);
	}
	else if (reason_to_call == DLL_PROCESS_DETACH)
		on_dll_detach();

	return true;
}
