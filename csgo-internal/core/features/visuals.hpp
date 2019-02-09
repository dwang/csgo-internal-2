#pragma once

#include "../../dependencies/utilities/singleton.hpp"
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

public:
	void render();
};
