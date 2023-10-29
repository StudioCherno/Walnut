#include "Walnut/Application.h"

#include "Common.h"
#include "Settings.h"

class ExampleUI : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		auto dockspace_id = ImGui::GetID("VulkanAppDockspace");
		ImGui::Begin("Lunanic", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::DockBuilderDockWindow("Lunanic", dockspace_id);

		if (ImGui::InputText("String", g_Settings.Options["String"].get<std::string*>()))
			g_Settings.Save();

		if (ImGui::InputScalar("Integer", ImGuiDataType_U64, g_Settings.Options["Integer"].get<uint64_t*>()))
			g_Settings.Save();

		if (ImGui::InputScalar("Float", ImGuiDataType_Float, g_Settings.Options["Float"].get<double*>()))
			g_Settings.Save();

		const int min = 0, max = 255;
		if (ImGui::SliderScalar("Byte", ImGuiDataType_U8, (PINT)g_Settings.Options["Byte"].get<uint64_t*>(), &min, &max))
			g_Settings.Save();

		const char* combo_options[] = { "Banana", "Apple", "Pineapple", "Mango", "Grape", "Strawberry" };
		if (ImGui::Combo("Combo", (PINT)g_Settings.Options["Combo"].get<int64_t*>(), combo_options, IM_ARRAYSIZE(combo_options)))
			g_Settings.Save();

		if (ImGui::RadioButton("One", (PINT)g_Settings.Options["Radio"].get<int64_t*>(), 0)) g_Settings.Save(); ImGui::SameLine();
		if (ImGui::RadioButton("Two", (PINT)g_Settings.Options["Radio"].get<int64_t*>(), 1)) g_Settings.Save(); ImGui::SameLine();
		if (ImGui::RadioButton("Three", (PINT)g_Settings.Options["Radio"].get<int64_t*>(), 2)) g_Settings.Save();

		if (ImGui::Checkbox("Bool", g_Settings.Options["Bool"].get<bool*>()))
			g_Settings.Save();

		if (ImGui::Button("LogToClipboard"))
		{
			ImGui::LogToClipboard();
			ImGui::LogText("LogToClipboard");
		}
		ImGui::Separator();
		ImGui::Text("github.com/gnireorb/lunanic");
		ImGui::End();
	}
};