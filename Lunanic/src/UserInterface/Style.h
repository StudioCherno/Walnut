#include "Walnut/Application.h"

#include "Common.h"

class Style
{
public:
	static inline void Apply()
	{
		ImGui::GetIO().IniFilename = { nullptr };

		ImGui::GetStyle().WindowRounding = 4.0f;
		ImGui::GetStyle().FrameRounding = 4.0f;
		ImGui::GetStyle().FramePadding = ImVec2(5, 5);
		ImGui::GetStyle().GrabRounding = 4.0f;
		ImGui::GetStyle().ChildRounding = 4.0f;
		ImGui::GetStyle().WindowTitleAlign = { 0.5f, 0.5f };

		ImGui::StyleColorsDark();

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.93f, 0.94f, 0.95f, 0.58f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.09f, 0.15f, 0.95f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.18f, 0.29f, 0.58f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.14f, 0.21f, 0.92f);
		colors[ImGuiCol_Border] = ImVec4(0.06f, 0.09f, 0.15f, 0.39f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.06f, 0.09f, 0.15f, 0.20f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.25f, 0.40f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.28f, 0.40f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.21f, 0.37f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.25f, 0.40f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.18f, 0.29f, 0.47f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.18f, 0.29f, 0.47f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.12f, 0.18f, 0.29f, 0.50f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.12f, 0.18f, 0.29f, 0.86f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.12f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.12f, 0.18f, 0.29f, 0.76f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.12f, 0.22f, 0.40f, 0.86f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.22f, 0.28f, 0.40f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.93f, 0.93f, 0.95f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.93f, 0.93f, 0.95f, 0.50f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.93f, 0.93f, 0.95f, 0.50f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.12f, 0.18f, 0.29f, 0.76f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.12f, 0.22f, 0.40f, 0.86f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.17f, 0.27f, 0.42f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.18f, 0.29f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.12f, 0.22f, 0.40f, 0.86f);
		colors[ImGuiCol_TabActive] = ImVec4(0.17f, 0.27f, 0.42f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.85f, 0.87f, 0.88f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.86f, 0.87f, 0.88f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.21f, 0.29f, 0.42f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.12f, 0.18f, 0.29f, 0.73f);
	}
};

inline Style g_Style;
