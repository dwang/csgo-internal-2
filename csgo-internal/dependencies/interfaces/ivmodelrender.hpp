#pragma once

#include "../utilities/utilities.hpp"
#include "../../sdk/structs/materials.hpp"

class iv_model_render
{
public:
	void override_material(i_material* material)
	{
		return utilities::get().call_vfunc<1, void>(this, material, 0, 0);
	}
};