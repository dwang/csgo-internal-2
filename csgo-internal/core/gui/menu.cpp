#include "menu.hpp"

#include <vector>
#include "settings.hpp"
#include "../../utilities/globals.hpp"

void menu::initialize()
{
	style.Alpha = 1.0f;                              // Global alpha applies to everything in ImGui
	style.WindowPadding = ImVec2(10, 10);            // Padding within a window
	style.WindowMinSize = ImVec2(100, 100);          // Minimum window size
	style.WindowRounding = 0.0f;                     // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);     // Alignment for title bar text
	style.ChildRounding = 0.0f;                      // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	style.FramePadding = ImVec2(5, 5);               // Padding within a framed rectangle (used by most widgets)
	style.FrameRounding = 0.0f;                      // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(5, 5);                // Horizontal and vertical spacing between widgets/lines
	style.ItemInnerSpacing = ImVec2(4, 4);           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	style.TouchExtraPadding = ImVec2(0, 0);          // Expand reactive bounding box for touch-based system where touch position is not accurate enough.
	style.IndentSpacing = 21.0f;                     // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	style.ColumnsMinSpacing = 6.0f;                  // Minimum horizontal spacing between two columns
	style.ScrollbarSize = 16.0f;                     // Width of the vertical scrollbar, Height of the horizontal scrollbar
	style.ScrollbarRounding = 9.0f;                  // Radius of grab corners rounding for scrollbar
	style.GrabMinSize = 10.0f;                       // Minimum width/height of a grab box for slider/scrollbar
	style.GrabRounding = 0.0f;                       // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);      // Alignment of button text when button is larger than text.
	style.DisplayWindowPadding = ImVec2(22, 22);     // Window positions are clamped to be IsVisible within the display area by at least this amount. Only covers regular windows.
	style.DisplaySafeAreaPadding = ImVec2(4, 4);     // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	style.AntiAliasedLines = true;                   // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	style.AntiAliasedFill = true;                    // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	style.CurveTessellationTol = 1.25f;              // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.


	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.58f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.15f, 0.60f, 0.78f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.0f); // 
	style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.15f, 0.60f, 0.78f, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);

	render_tab["aimbot"] = []()
	{
		ImGui::Checkbox("backtrack", &settings::get().aimbot.backtrack);
		if (settings::get().aimbot.backtrack)
			ImGui::SliderInt("ticks", &settings::get().aimbot.backtrack_ticks, 1, 12);
	};

	render_tab["visuals"] = []()
	{
		const char* items[] = { "off", "on", "dead" };

		if (ImGui::BeginCombo("##esp", items[settings::get().visuals.esp_mode]))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (items[settings::get().visuals.esp_mode] == items[n]);
				if (ImGui::Selectable(items[n], is_selected))
				{
					settings::get().visuals.esp_mode = n;
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (settings::get().visuals.esp_mode != 0)
		{
			ImGui::Checkbox("box esp", &settings::get().visuals.box_esp);
			ImGui::Checkbox("name esp", &settings::get().visuals.name_esp);
		}

		ImGui::Checkbox("chams", &settings::get().visuals.chams);
		if (settings::get().visuals.chams)
			ImGui::Checkbox("chams ignore z", &settings::get().visuals.chams_ignore_z);
		ImGui::Checkbox("watermark", &settings::get().visuals.watermark);
	};

	render_tab["misc"] = []()
	{
		ImGui::Checkbox("bunnyhop", &settings::get().misc.bunnyhop);
		ImGui::Checkbox("stream proof", &settings::get().misc.stream_proof);
		if (ImGui::Button("unload", ImVec2(100, 30)))
			globals::get().unload = true;
	};

	render_tab["skins"] = []()
	{
		ImGui::Text("Skins");
	};
}

void menu::render()
{
	const std::vector<std::string> tabs = { "aimbot", "visuals", "misc", "skins" };
	constexpr int width = 400;
	ImGui::GetStyle() = style;

	ImGui::SetNextWindowSize({ static_cast<float>(width), static_cast<float>(tabs.size()) * 50 + 40 + 3 });

	if (ImGui::Begin("csgo-internal", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, "##cols", false);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

		for (unsigned i = 0; i < tabs.size(); i++)
		{
			if (i == active_tab)
				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.70f, 0.95f, 1.00f);
			else
				ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

			if (ImGui::Button(tabs[i].c_str(), ImVec2(150, 50)))
				active_tab = i;
		}

		ImGui::PopStyleVar();
		ImGui::SetColumnOffset(0, -(width / 2 - 150 - 20));
		ImGui::NextColumn();
		render_tab[tabs[active_tab]]();
		ImGui::End();
	}
}
