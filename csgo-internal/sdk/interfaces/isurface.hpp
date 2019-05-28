#pragma once

#include "../../utilities/utilities.hpp"
#include "../../sdk/misc/vertex_t.hpp"

class i_surface
{
public:
	void set_drawing_color(int r, int g, int b, int a = 255)
	{
		return utilities::get().call_vfunc<15, void>(this, r, g, b, a);
	}
	
	void draw_filled_rectangle(int x, int y, int w, int h)
	{
		return utilities::get().call_vfunc<16, void>(this, x, y, x + w, y + h);
	}

	void draw_outlined_rect(int x, int y, int w, int h)
	{
		return utilities::get().call_vfunc<18, void>(this, x, y, x + w, y + h);
	}

	void draw_line(int x1, int y1, int x2, int y2)
	{
		return utilities::get().call_vfunc<19, void>(this, x1, y1, x2, y2);
	}

	void draw_text_font(unsigned long font)
	{
		return utilities::get().call_vfunc<23, void>(this, font);
	}

	void set_text_color(int r, int g, int b, int a = 255)
	{
		return utilities::get().call_vfunc<25, void>(this, r, g, b, a);
	}

	void draw_text_pos(int x, int y)
	{
		return utilities::get().call_vfunc<26, void>(this, x, y);
	}

	void draw_render_text(const wchar_t* text, int text_length)
	{
		return utilities::get().call_vfunc<28, void>(this, text, text_length, 0);
	}

	void set_texture_rgba(int id, const unsigned char* rgba, int wide, int tall)
	{
		return utilities::get().call_vfunc<37, void>(this, id, rgba, wide, tall, 0, false);
	}

	void set_texture(int id)
	{
		return utilities::get().call_vfunc<38, void>(this, id);
	}

	int create_new_texture_id(bool procedural = false)
	{
		return utilities::get().call_vfunc<43, int>(this, procedural);
	}

	unsigned long font_create()
	{
		return utilities::get().call_vfunc<71, unsigned int>(this);
	}

	void set_font_glyph(unsigned long font, const char* font_name, int tall, int weight, int blur, int scanlines, int flags)
	{
		return utilities::get().call_vfunc<72, void>(this, font, font_name, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		return utilities::get().call_vfunc<79, void>(this, font, text, &wide, &tall);
	}

	void draw_polygon(int n, vertex_t* vertice, bool clip_vertices = true)
	{
		return utilities::get().call_vfunc<106, void>(this, n, vertice, clip_vertices);
	}
};
