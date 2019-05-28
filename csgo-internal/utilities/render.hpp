#pragma once

#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"
#include "../../imgui/imgui_impl_dx9.h"
#include "../../imgui/imgui_impl_win32.h"

#include "singleton.hpp"
#include "globals.hpp"
#include "utilities.hpp"
#include "interfaces.hpp"
#include "../sdk/misc/color.hpp"

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

		interfaces::get().surface->set_font_glyph(default_font, "Tahoma", 12, 500, 0, 0, font_flags::fontflag_dropshadow);
		interfaces::get().surface->set_font_glyph(esp_font, "Verdana", 12, 500, 0, 0, font_flags::fontflag_antialias | font_flags::fontflag_dropshadow);
	}

	void draw_line(int x1, int y1, int x2, int y2, color col)
	{
		interfaces::get().surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->draw_line(x1, y1, x2, y2);
	}

	void draw_text(int x, int y, unsigned long font, const wchar_t* string, color col)
	{
		interfaces::get().surface->set_text_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->draw_text_font(font);
		interfaces::get().surface->draw_text_pos(x, y);
		interfaces::get().surface->draw_render_text(string, wcslen(string));
	}

	void draw_text(int x, int y, unsigned long font, std::string string, bool text_centered, color col)
	{
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* converted_text = text.c_str();

		int width, height;
		interfaces::get().surface->get_text_size(font, converted_text, width, height);

		interfaces::get().surface->set_text_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->draw_text_font(font);

		if (text_centered)
			interfaces::get().surface->draw_text_pos(x - (width / 2), y);
		else
			interfaces::get().surface->draw_text_pos(x, y);

		interfaces::get().surface->draw_render_text(converted_text, wcslen(converted_text));
	}

	void draw_rect(int x, int y, int w, int h, color col)
	{
		interfaces::get().surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->draw_outlined_rect(x, y, w, h);
	}

	void draw_filled_rect(int x, int y, int w, int h, color col)
	{
		interfaces::get().surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->draw_filled_rectangle(x, y, w, h);
	}

	void draw_outline(int x, int y, int w, int h, color col)
	{
		interfaces::get().surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->draw_outlined_rect(x, y, w, h);
	}

	void draw_textured_polygon(int n, vertex_t* vertice, color col)
	{
		static int texture_id = interfaces::get().surface->create_new_texture_id(true);
		static unsigned char buf[4] = { 255, 255, 255, 255 };
		interfaces::get().surface->set_texture_rgba(texture_id, buf, 1, 1);
		interfaces::get().surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::get().surface->set_texture(texture_id);
		interfaces::get().surface->draw_polygon(n, vertice);
	}

	void draw_circle(int x, int y, int r, int s, color col)
	{
		float step = M_PI * 2.0 / s;
		for (float a = 0; a < (M_PI * 2.0); a += step)
		{
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a + step) + x;
			float y2 = r * sin(a + step) + y;
			interfaces::get().surface->set_drawing_color(col.r, col.g, col.b, col.a);
			interfaces::get().surface->draw_line(x1, y1, x2, y2);
		}
	}

	void get_text_size(unsigned long font, std::string string, int w, int h)
	{
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* out = text.c_str();

		interfaces::get().surface->get_text_size(font, out, w, h);
	}

	vec2_t get_screen_size(vec2_t area)
	{
		static int old_w, old_h;
		interfaces::get().engine->get_screen_size((int&)area.x, (int&)area.y);

		if ((int&)area.x != old_w || (int&)area.y != old_h)
		{
			old_w = (int&)area.x;
			old_h = (int&)area.y;
			return vec2_t(old_w, old_h);
		}
		return area;
	}
};
