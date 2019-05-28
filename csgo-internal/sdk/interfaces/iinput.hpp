#pragma once

#include "../utilities/utilities.hpp"
#include "../../sdk/classes/c_usercmd.hpp"

class i_input
{
public:
	char pad_0x00[0x0C]; // 0x00
	bool m_trackir_available; //0x0C
	bool m_mouse_initiated; //0x0D
	bool m_mouse_active; //0x0E
	char pad_0x0F[0xFBE];

	c_usercmd* get_user_cmd(int slot, int sequence_num)
	{
		return utilities::get().call_vfunc<8, c_usercmd*>(this, slot, sequence_num);
	}
};
