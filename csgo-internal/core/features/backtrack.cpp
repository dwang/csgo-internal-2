#include "backtrack.hpp"

#include "../../dependencies/utilities/globals.hpp"
#include "../../dependencies/interfaces/interfaces.hpp"
#include "../../dependencies/utilities/utilities.hpp"
#include "../menu/settings.hpp"

void backtrack::create_move(c_usercmd* user_cmd)
{
	int best_target = -1;
	float best_fov = 90.f;

	if (globals::get().local_player->life_state() != 0)
		return;

	for (int i = 1; i <= interfaces::get().globals->max_clients; i++)
	{
		auto player = reinterpret_cast<player_t*>(interfaces::get().entity_list->get_client_entity(i));

		if (!player || !globals::get().local_player || !player->is_valid())
			continue;

		if (player == globals::get().local_player)
			continue;

		if (player->team() == globals::get().local_player->team())
			continue;

		data[i][user_cmd->command_number % settings::get().aimbot.backtrack_ticks + 1] = backtrack_tick{ player->simulation_time(), player->get_bone_position(8) };
		vec3_t view_direction = angle_vector(user_cmd->view_angles);
		float fov = distance_point_to_line(player->get_bone_position(8), globals::get().local_player->get_bone_position(8), view_direction);

		if (best_fov > fov)
		{
			best_fov = fov;
			best_target = i;
		}
	}

	float best_target_simulation_time = 0.f;

	if (best_target != -1)
	{
		float temp = FLT_MAX;
		vec3_t view_direction = angle_vector(user_cmd->view_angles);

		for (int t = 0; t < settings::get().aimbot.backtrack_ticks; ++t)
		{
			float fov = distance_point_to_line(data[best_target][t].hitbox_position, globals::get().local_player->get_bone_position(8), view_direction);
			if (temp > fov && data[best_target][t].simulation_time > globals::get().local_player->simulation_time() - 1)
			{
				temp = fov;
				best_target_simulation_time = data[best_target][t].simulation_time;
			}
		}

		if (user_cmd->buttons & in_attack)
			user_cmd->tick_count = static_cast<int>(0.5f + best_target_simulation_time / interfaces::get().globals->interval_per_tick);
	}
}

vec3_t backtrack::angle_vector(vec3_t to_convert)
{
	auto y_sin = sin(to_convert.y / 180.f * static_cast<float>(M_PI));
	auto y_cos = cos(to_convert.y / 180.f * static_cast<float>(M_PI));

	auto x_sin = sin(to_convert.x / 180.f * static_cast<float>(M_PI));
	auto x_cos = cos(to_convert.x / 180.f * static_cast<float>(M_PI));

	return vec3_t(x_cos * y_cos, x_cos * y_sin, -x_sin);
}

float backtrack::distance_point_to_line(vec3_t point, vec3_t origin, vec3_t direction)
{
	auto delta = point - origin;

	auto temp_offset = delta.dot(direction) / (direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
	if (temp_offset < 0.000001f)
		return FLT_MAX;

	auto perpendicular_point = origin + (direction * temp_offset);
	return (point - perpendicular_point).length();
}
