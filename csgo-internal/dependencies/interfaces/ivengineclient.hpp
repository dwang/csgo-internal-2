#pragma once

#include <cstdint>

#include "../utilities/utilities.hpp"
#include "../../sdk/math/vector.hpp"

struct player_info_t
{
	int64_t __pad0;
	union
	{
		int64_t xuid;
		struct
		{
			int xuidlow;
			int xuidhigh;
		};
	};
	char name[128];
	int userid;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
};

class iv_engine_client
{
public:
	void get_screen_size(int& width, int& height)
	{
		return utilities::get().call_vfunc<5, void>(this, &width, &height);
	}

	void get_player_info(int index, player_info_t *info)
	{
		return utilities::get().call_vfunc<8, void>(this, index, info);
	}

	int get_player_for_user_id(int user_id)
	{
		return utilities::get().call_vfunc<9, int>(this, user_id);
	}

	int get_local_player()
	{
		return utilities::get().call_vfunc<12, int>(this);
	}

	vec3_t get_view_angles()
	{
		vec3_t temp;
		utilities::get().call_vfunc<18, void>(this, temp);
		return temp;
	}

	void set_view_angles(vec3_t& angles)
	{
		return utilities::get().call_vfunc<19, void>(this, &angles);
	}

	void execute_cmd(const char* cmd)
	{
		return utilities::get().call_vfunc<108, void>(this, cmd);
	}
};
