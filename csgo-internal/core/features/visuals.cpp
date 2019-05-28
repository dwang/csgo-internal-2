#include "visuals.hpp"

#include "../gui/settings.hpp"
#include "../../utilities/interfaces.hpp"
#include "../../utilities/globals.hpp"
#include "../../utilities/render.hpp"

bool visuals::get_bounding_box(entity_t* entity, box& in)
{
	origin = entity->origin();
	min = entity->collideable()->mins() + origin;
	max = entity->collideable()->maxs() + origin;

	vec3_t points[] =
	{
		vec3_t(min.x, min.y, min.z),
		vec3_t(min.x, max.y, min.z),
		vec3_t(max.x, max.y, min.z),
		vec3_t(max.x, min.y, min.z),
		vec3_t(max.x, max.y, max.z),
		vec3_t(min.x, min.y, max.z),
		vec3_t(min.x, max.y, max.z),
		vec3_t(max.x, min.y, max.z)
	};

	if (!interfaces::get().debug_overlay->world_to_screen(points[3], flb) || !interfaces::get().debug_overlay->world_to_screen(points[5], brt) ||
		!interfaces::get().debug_overlay->world_to_screen(points[0], blb) || !interfaces::get().debug_overlay->world_to_screen(points[4], frt) ||
		!interfaces::get().debug_overlay->world_to_screen(points[2], frb) || !interfaces::get().debug_overlay->world_to_screen(points[1], brb) ||
		!interfaces::get().debug_overlay->world_to_screen(points[6], blt) || !interfaces::get().debug_overlay->world_to_screen(points[7], flt))
		return false;

	vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	in.x = static_cast<int>(left);
	in.y = static_cast<int>(top);
	in.w = static_cast<int>(right - left);
	in.h = static_cast<int>(bottom - top);

	return true;
}

void visuals::render()
{
	for (int i = 1; i <= interfaces::get().globals->max_clients; i++)
	{
		if (settings::get().visuals.esp_mode == 0)
			continue;

		auto player = reinterpret_cast<player_t*>(interfaces::get().entity_list->get_client_entity(i));

		if (!player || !globals::get().local_player || !player->is_valid())
			continue;

		if (player == globals::get().local_player)
			continue;

		if (player->team() == globals::get().local_player->team())
			continue;

		if (settings::get().visuals.esp_mode == 2 && globals::get().local_player->life_state() == 0)
			continue;
	
		if (!get_bounding_box(player, bounding_box))
			continue;

		interfaces::get().engine->get_player_info(i, &player_info);

		if (settings::get().visuals.box_esp)
			draw_player_box(player, bounding_box);

		if (settings::get().visuals.name_esp)
			draw_player_name(player, player_info, bounding_box);
	}
}

void visuals::draw_player_box(entity_t* player, box bounding_box)
{
	render::get().draw_rect(bounding_box.x, bounding_box.y, bounding_box.w, bounding_box.h, color(255, 255, 255, 255));
}

void visuals::draw_player_name(entity_t* player, player_info_t player_info, box bounding_box)
{
	render::get().draw_text(bounding_box.x + (bounding_box.w / 2), bounding_box.y - 20, render::get().esp_font, player_info.name, true, color(255, 255, 255, 255));
}
