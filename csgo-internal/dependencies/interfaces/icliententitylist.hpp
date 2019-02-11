#pragma once

#include <cstdint>

#include "../utilities/utilities.hpp"

class i_client_entity_list
{
public:
	void* get_client_entity(int index)
	{
		return utilities::get().call_vfunc<3, void*>(this, index);
	}

	void* get_client_entity(std::uintptr_t handle)
	{
		return utilities::get().call_vfunc<4, void*>(this, handle);
	}
};
