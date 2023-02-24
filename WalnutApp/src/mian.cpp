#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

enum TaskStatus
{
	ONGOING,
	CLOSED
};

//czerwony kolor ImVec4(1.0f, 0.0f, 0.0f, 1.0f)

struct Task
{
	std::string description;
	bool completed;
	TaskStatus status;
};

std::vector<Task> tasks;
std::vector<int> ongoingTasks;
std::vector<int> closedTasks;

static char Input[256] = "";
//static char editInput[256] = "";
static bool TaskAdded = false;
static int selectedTask = -1; //index zaznaczonych taskow do edycji


//Funkcja odpowiedzialna za popup i edytowanie taskow
void Editor()
{
	if (selectedTask >= 0)
	{
		ImGui::OpenPopup("Edit Task");
		if (ImGui::BeginPopupModal("Edit Task", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::InputText("Task Description", Input, sizeof(Input));
			if (ImGui::Button("Save"))
			{
				tasks[selectedTask].description = Input;
				Input[0] = '\0';
				selectedTask = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				Input[0] = '\0';
				selectedTask = -1;
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::EndPopup();
	}
}
//status taskow
void StatusDashboard()
{
	ImGui::Begin("Status");

	//dashbord trwajace taski
	ImGui::BeginChild("Ongoing Tasks", ImVec2(0, 200), true);
	ImGui::Text("Ongoing Tasks (%d)", ongoingTasks.size());
	if (!TaskAdded)
	{
		for (int i = 0; i < ongoingTasks.size(); i++)
		{
			int index = ongoingTasks[i];
			Task& task = tasks[index];
			std::string taskLabel =  task.description;
			if (ImGui::Checkbox(taskLabel.c_str(), &task.completed))
			{
				//zmien status jak checkbox jest zaznaczony
				task.status = task.completed ? TaskStatus::CLOSED : TaskStatus::ONGOING;

				if (task.status == TaskStatus::CLOSED)
				{
					closedTasks.push_back(index);
					ongoingTasks.erase(ongoingTasks.begin() + i);
					i--;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button(("Edit##" + std::to_string(index)).c_str()))
			{
				selectedTask = index;
				std::strcpy(Input, task.description.c_str());
			}
			ImGui::SameLine();
			if (ImGui::Button(("Delete##" + std::to_string(i)).c_str()))
			{
				tasks.erase(tasks.begin() + index);
				ongoingTasks.erase(ongoingTasks.begin() + i);
				for (int j = 0; j < ongoingTasks.size(); j++)
				{
					if (ongoingTasks[j] > index)
					{
						ongoingTasks[j]--;
					}
				}
				for (int j = 0; j < closedTasks.size(); j++)
				{
					if (closedTasks[j] > index)
					{
						closedTasks[j]--;
					}
				}
				i = -1; //restart petli
			}
		}
	}
	ImGui::EndChild();

	//dashboard zamkniete taski
	ImGui::BeginChild("Closed Tasks", ImVec2(0, 200), true);
	ImGui::Text("Closed Tasks (%d)", closedTasks.size());
	if (!TaskAdded)
	{
		for (int i = 0; i < closedTasks.size(); i++)
		{
			int index = closedTasks[i];
			Task& task = tasks[index];
			std::string taskLabel = task.description;
			if (ImGui::Checkbox(taskLabel.c_str(), &task.completed))
			{
				//zmien status jak checkbox jest zaznaczony
				task.status = task.completed ? TaskStatus::CLOSED : TaskStatus::ONGOING;

				if (task.status == TaskStatus::CLOSED)
				{
					closedTasks.push_back(index);
					for (int j = 0; j < ongoingTasks.size(); j++)
					{
						if (ongoingTasks[j] == index)
						{
							ongoingTasks.erase(ongoingTasks.begin() + j);
							break;
						}
					}
				}
				else
				{
					ongoingTasks.push_back(index);
					for (int j = 0; j < closedTasks.size(); j++)
					{
						if (closedTasks[j] == index)
						{
							closedTasks.erase(closedTasks.begin() + j);
							break;
						}
					}
				}
			}
			ImGui::SameLine();

			//funkcja odpowiedzialna za edytowanie w przypadku zamknietych wylaczona

			/*if (ImGui::Button(("Edit##" + std::to_string(index)).c_str()))
			{
				selectedTask = index;
				std::strcpy(Input, task.description.c_str());
			}
			ImGui::SameLine();*/


			if (ImGui::Button(("Delete##" + std::to_string(index)).c_str()))
			{
				if (tasks[index].status == TaskStatus::ONGOING) 
				{
					for (int j = 0; j < ongoingTasks.size(); j++) 
					{
						if (ongoingTasks[j] == index) 
						{
							ongoingTasks.erase(ongoingTasks.begin() + j);
							break;
						}
					}
				}
				else 
				{
					for (int j = 0; j < closedTasks.size(); j++) 
					{
						if (closedTasks[j] == index) 
						{
							closedTasks.erase(closedTasks.begin() + j);
							break;
						}
					}
				}
				tasks.erase(tasks.begin() + index);
				for (int j = 0; j < ongoingTasks.size(); j++) 
				{
					if (ongoingTasks[j] > index) 
					{
						ongoingTasks[j]--;
					}
				}
				for (int j = 0; j < closedTasks.size(); j++) 
				{
					if (closedTasks[j] > index) 
					{
						closedTasks[j]--;
					}
				}
				i = -1; //restart petli
			}
		}
	}
	
	ImGui::EndChild();

	ImGui::End();
}
//dodawanie taskow
void taskAddeer()
{
	ImGui::Begin("Tasker");
	ImGui::Text("Task Description");
	ImGui::SameLine();
	ImGui::InputText("##Task Description", Input, sizeof(Input));

	if (ImGui::Button("Add Task", ImVec2(150.0f, 0.0f)) && Input[0] != '\0' && !std::isspace(Input[0]))
	{
		tasks.push_back({ Input, false, TaskStatus::ONGOING });
		Input[0] = '\0';
		TaskAdded = true;

		if (tasks.back().status == TaskStatus::ONGOING)
		{
			ongoingTasks.push_back(tasks.size() - 1);
		}
		else
		{
			closedTasks.push_back(tasks.size() - 1);
		}

	}
	else
	{
		TaskAdded = false;
	}

	ImGui::End();
}

class ExampleLayer : public Walnut::Layer
{
public:

	virtual void OnUIRender() override
	{
		
		taskAddeer();
		Editor();
		StatusDashboard();

		//ImGui::ShowDemoWindow();
	}
};



Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Tasker_Inz_WSB";

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
		}

		
	});
	return app;
}