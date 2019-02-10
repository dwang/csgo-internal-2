#pragma once

#include "../../dependencies/utilities/singleton.hpp"
#include "../../sdk/sdk.hpp"

class backtrack : public singleton<backtrack>
{
private:
	struct backtrack_tick
	{
		float simulation_time;
		vec3_t hitbox_position;
		vec3_t origin;

	};
	backtrack_tick data[64][12];

	vec3_t angle_vector(vec3_t to_convert);
	float distance_point_to_line(vec3_t point, vec3_t origin, vec3_t direction);

public:
	void create_move(c_usercmd* user_cmd);
};