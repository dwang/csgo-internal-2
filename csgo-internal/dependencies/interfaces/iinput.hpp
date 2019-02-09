#pragma once

#pragma once

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
		using original_fn = c_usercmd * (__thiscall*)(void*, int, int);
		return (*(original_fn**)this)[8](this, slot, sequence_num);
	}
};
