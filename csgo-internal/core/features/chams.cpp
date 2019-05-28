#include "chams.hpp"

#include "../../utilities/interfaces.hpp"
#include "../../utilities/globals.hpp"
#include "../gui/settings.hpp"

void chams::setup()
{
	std::ofstream("csgo\\materials\\simple_regular.vmt") << R"#("VertexLitGeneric"
		{
			"$basetexture" "vgui/white_additive"
			"$ignorez"      "0"
			"$envmap"       ""
			"$nofog"        "1"
			"$model"        "1"
			"$nocull"       "0"
			"$selfillum"    "1"
			"$halflambert"  "1"
			"$znearer"      "0"
			"$flat"         "1"
		}
	)#";

	std::ofstream("csgo\\materials\\simple_ignorez.vmt") << R"#("VertexLitGeneric"
		{
			"$basetexture" "vgui/white_additive"
			"$ignorez"      "1"
			"$envmap"       ""
			"$nofog"        "1"
			"$model"        "1"
			"$nocull"       "0"
			"$selfillum"    "1"
			"$halflambert"  "1"
			"$znearer"      "0"
			"$flat"         "1"
		}
	)#";

	simple_regular = interfaces::get().material_system->find_material("simple_regular", "Model textures");
	simple_ignorez = interfaces::get().material_system->find_material("simple_ignorez", "Model textures");

}

void chams::scene_end()
{
	static bool once = false;

	if (!once)
	{
		setup();
		once = true;
	}

	for (int i = 1; i < interfaces::get().globals->max_clients; i++)
	{
		auto player = reinterpret_cast<player_t*>(interfaces::get().entity_list->get_client_entity(i));

		if (!player || !globals::get().local_player || !player->is_valid())
			continue;

		if (settings::get().visuals.chams_ignore_z)
		{
			if (player->team() == globals::get().local_player->team())
				interfaces::get().render_view->set_color_modulation(1.0f, 1.0f, 1.0f);
			else
				interfaces::get().render_view->set_color_modulation(255.0f / 255.0f, 105.0f / 255.0f, 180.0f / 255.0f);

			interfaces::get().model_render->override_material(simple_ignorez);
			player->draw_model(0x1, 255);
		}

		if (player->team() == globals::get().local_player->team())
			interfaces::get().render_view->set_color_modulation(30.0f / 255.0f, 144.0f / 255.0f, 255.0f / 255.0f);
		else
			interfaces::get().render_view->set_color_modulation(150.0f / 255.0f, 200.0f / 255.0f, 60.0f / 255.0f);

		interfaces::get().model_render->override_material(simple_regular);
		player->draw_model(0x1, 255);

		interfaces::get().model_render->override_material(nullptr);
	}
}
