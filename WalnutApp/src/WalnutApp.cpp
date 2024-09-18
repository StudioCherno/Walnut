#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}else if(ImGui::BeginMenu("Help"))
		{
			if(ImGui::MenuItem("About"))
			{
				ImGui::Begin("About", &show_about_dialog, ImGuiWindowFlags_AlwaysAutoResize);

        		ImGui::Text("Walnut");
        		ImGui::Separator();
        		ImGui::Text("Version: 1.0.0");
        		ImGui::Text("Developed by: Cherno");
        		ImGui::Text("Website: https://github.com/thecherno");

			}
				ImGui::EndMenu();
		}
	});
	return app;
}