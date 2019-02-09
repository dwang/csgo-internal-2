#pragma once

class i_input_system
{
public:
	void enable_input(bool enable)
	{
		using original_fn = void(__thiscall*)(void*, bool);
		return (*(original_fn**)this)[11](this, enable);
	}

	void reset_input_state()
	{
		using original_fn = void(__thiscall*)(void*);
		return (*(original_fn**)this)[39](this);
	}
};
