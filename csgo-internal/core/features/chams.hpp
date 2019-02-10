#pragma once

#include "../../dependencies/utilities/singleton.hpp"
#include "../../sdk/sdk.hpp"

class chams : public singleton<chams>
{
public:
	void scene_end();

private:
	void setup();
	i_material* simple_regular;
	i_material* simple_ignorez;
};