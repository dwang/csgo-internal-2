#pragma once

#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"

#include "singleton.hpp"
#include "globals.hpp"
#include "utilities.hpp"
#include "../interfaces/interfaces.hpp"
#include "../../sdk/misc/color.hpp"

enum font_flags
{
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

class render : public singleton<render>
{
public:
	DWORD default_font;
	DWORD esp_font;

public:
	void initialize(IDirect3DDevice9* device)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(globals::get().window);
		ImGui_ImplDX9_Init(device);

		default_font = interfaces::get().surface->font_create();
		esp_font = interfaces::get().surface->font_create();

		interfaces::get().surface->set_font_glyph(default_font, "Tahoma", 20, FW_MEDIUM, 0, 0, font_flags::fontflag_outline);
		interfaces::get().surface->set_font_glyph(esp_font, "Verdana", 20, FW_BOLD, 0, 0, font_flags::fontflag_dropshadow);

	}

	void draw_line(int x1, int y1, int x2, int y2, color draw_color)
	{
		interfaces::get().surface->set_drawing_color(draw_color.r, draw_color.g, draw_color.b, draw_color.a = 255);
		interfaces::get().surface->draw_line(x1, y1, x2, y2);
	}

	void draw_text(int x, int y, unsigned long font, const char* string, bool text_centered, color draw_color)
	{
		va_list va_alist;
		char buf[1024];
		va_start(va_alist, string);
		_vsnprintf_s(buf, sizeof(buf), string, va_alist);
		va_end(va_alist);
		wchar_t wbuf[1024];
		MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

		int width, height;
		interfaces::get().surface->get_text_size(font, wbuf, width, height);

		interfaces::get().surface->set_text_color(draw_color.r, draw_color.g, draw_color.b, draw_color.a = 255);
		interfaces::get().surface->draw_text_font(font);

		if (text_centered)
			interfaces::get().surface->draw_text_pos(x - (width / 2), y);
		else
			interfaces::get().surface->draw_text_pos(x, y);

		interfaces::get().surface->draw_render_text(wbuf, wcslen(wbuf));
	}

	void draw_text(int x, int y, unsigned long font, std::string string, bool text_centered, color draw_color)
	{
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* converted_text = text.c_str();

		int width, height;
		interfaces::get().surface->get_text_size(font, converted_text, width, height);

		interfaces::get().surface->set_text_color(draw_color.r, draw_color.g, draw_color.b, draw_color.a = 255);
		interfaces::get().surface->draw_text_font(font);
		if (text_centered)
			interfaces::get().surface->draw_text_pos(x - (width / 2), y);
		else
			interfaces::get().surface->draw_text_pos(x, y);
		interfaces::get().surface->draw_render_text(converted_text, wcslen(converted_text));
	}

	void draw_filled_rect(int x, int y, int w, int h, color draw_color)
	{
		interfaces::get().surface->set_drawing_color(draw_color.r, draw_color.g, draw_color.b, draw_color.a = 255);
		interfaces::get().surface->draw_filled_rectangle(x, y, w, h);
	}

	void draw_outline(int x, int y, int w, int h, color draw_color)
	{
		interfaces::get().surface->set_drawing_color(draw_color.r, draw_color.g, draw_color.b, draw_color.a = 255);
		interfaces::get().surface->draw_outlined_rect(x, y, w, h);
	}

	void get_text_size(unsigned long font, const char *string, int w, int h)
	{
		va_list va_alist;
		char buf[1024];
		va_start(va_alist, string);
		_vsnprintf_s(buf, sizeof(buf), string, va_alist);
		va_end(va_alist);
		wchar_t out[1024];
		MultiByteToWideChar(CP_UTF8, 0, buf, 256, out, 256);

		interfaces::get().surface->get_text_size(font, out, w, h);
	}

	void get_text_size(unsigned long font, std::string string, int w, int h)
	{
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* out = text.c_str();

		interfaces::get().surface->get_text_size(font, out, w, h);
	}

	RECT get_text_size(DWORD font, const char* text, ...)
	{
		size_t original_size = strlen(text) + 1;
		const size_t new_size = 100;
		size_t converted_characters = 0;
		wchar_t wcstring[new_size];
		mbstowcs_s(&converted_characters, wcstring, original_size, text, _TRUNCATE);

		RECT rect; int x, y;
		interfaces::get().surface->get_text_size(font, wcstring, x, y);
		rect.left = x; rect.bottom = y;
		rect.right = x;
		return rect;
	}

	vec2_t get_screen_size(vec2_t area)
	{
		static int old_w, old_h;
		interfaces::get().engine->get_screen_size((int&)area.x, (int&)area.y);

		if ((int&)area.x != old_w || (int&)area.y != old_h)
		{
			old_w = (int&)area.x;
			old_h = (int&)area.y;

			return vec2_t(static_cast<float>(old_w), static_cast<float>(old_h));
		}
		return area;
	}
};
