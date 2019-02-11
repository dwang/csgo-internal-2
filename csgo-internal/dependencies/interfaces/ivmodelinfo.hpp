#pragma once

#include "../utilities/utilities.hpp"
#include "../../sdk/structs/models.hpp"
#include "../../sdk/classes/studio.hpp"

class iv_model_info
{
public:
	model_t* get_model(int index)
	{
		return utilities::get().call_vfunc<1, model_t*>(this, index);
	}

	int get_model_index(const char* filename)
	{
		return utilities::get().call_vfunc<2, int>(this, filename);
	}

	const char* get_model_name(const model_t* model)
	{
		return utilities::get().call_vfunc<3, const char*>(this, model);
	}

	studio_hdr_t* get_studio_model(const model_t* model)
	{
		return utilities::get().call_vfunc<32, studio_hdr_t*>(this, model);
	}
};
