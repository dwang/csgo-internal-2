#pragma once

#include "../utilities/utilities.hpp"
#include "../../sdk/structs/materials.hpp"

class i_material_system
{
public:
	i_material* find_material(char const* material_name, const char* group_name, bool complain = true, const char* complain_prefix = 0)
	{
		return utilities::get().call_vfunc<84, i_material*>(this, material_name, group_name, complain, complain_prefix);
	}

	material_handle_t first_material()
	{
		return utilities::get().call_vfunc<86, material_handle_t>(this);
	}

	material_handle_t next_material(material_handle_t handle)
	{
		return utilities::get().call_vfunc<87, material_handle_t>(this, handle);
	}

	material_handle_t invalid_material_handle()
	{
		return utilities::get().call_vfunc<88, material_handle_t>(this);
	}

	i_material* get_material(material_handle_t handle)
	{
		return utilities::get().call_vfunc<89, i_material*>(this, handle);
	}

	int	get_materials_count()
	{
		return utilities::get().call_vfunc<90, int>(this);
	}
};