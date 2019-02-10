#pragma once

#include "../../dependencies/utilities/singleton.hpp"
#include "../../dependencies/interfaces/ivengineclient.hpp"
#include "../../sdk/sdk.hpp"

class visuals : public singleton<visuals>
{
private:
	struct box
	{
		int x, y, w, h;
		box() = default;
		box(int x, int y, int w, int h)
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	bool get_bounding_box(entity_t* entity, box& in);
	void draw_player_box(entity_t* player, box bounding_box);
	void draw_player_name(entity_t* player, player_info_t player_info, box bounding_box);

public:
	void render();
};
