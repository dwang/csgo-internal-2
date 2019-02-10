#include "utilities.hpp"

#include <string>
#include <vector>

HMODULE utilities::get_handle_safe(std::string handle)
{
	while (!GetModuleHandleA(handle.c_str()))
		Sleep(50);

	return GetModuleHandleA(handle.c_str());
}

std::string utilities::format(const char *fmt, ...)
{
	char buf[1024];
	va_list arguments;

	va_start(arguments, fmt);
	_vsnprintf_s(buf, sizeof buf, fmt, arguments);
	va_end(arguments);

	return std::string(buf);
}

std::uint8_t* utilities::pattern_scan(void* module, const char* signature)
{
	static auto pattern_to_byte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
	
		return bytes;
	};

	auto dos_headers = (PIMAGE_DOS_HEADER)module;
	auto nt_headers = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dos_headers->e_lfanew);

	auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte(signature);
	auto scan_bytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = pattern_bytes.size();
	auto d = pattern_bytes.data();

	for (auto i = 0ul; i < size_of_image - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scan_bytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}
	
		if (found)
			return &scan_bytes[i];
	}

	return nullptr;
}
