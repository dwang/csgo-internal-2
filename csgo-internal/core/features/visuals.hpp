#pragma once

#include "../../dependencies/utilities/singleton.hpp"
#include "../../dependencies/interfaces/ivengineclient.hpp"
#include "../../sdk/sdk.hpp"

class visuals : public singleton<visuals>
{
private:
	vec3_t origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	box bounding_box;
	player_info_t player_info;

	bool get_bounding_box(entity_t* entity, box& in);
	void draw_player_box(entity_t* player, box bounding_box);
	void draw_player_name(entity_t* player, player_info_t player_info, box bounding_box);

public:
	void render();
};

