#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "UserInterface/Example.h"
#include "UserInterface/Style.h"

#include "Settings.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	g_Settings.Load();

	Walnut::ApplicationSpecification spec;
	spec.Name = "Lunanic";

	Walnut::Application* app = new Walnut::Application(spec);
	g_Style.Apply();
	app->PushLayer<ExampleUI>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}