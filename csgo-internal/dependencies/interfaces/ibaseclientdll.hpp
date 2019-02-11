#pragma once

#include "../utilities/utilities.hpp"
#include "../../sdk/classes/client_class.hpp"

class i_base_client_dll
{
public:
	client_class* get_client_classes()
	{
		return utilities::get().call_vfunc<8, client_class*>(this);
	}
};
