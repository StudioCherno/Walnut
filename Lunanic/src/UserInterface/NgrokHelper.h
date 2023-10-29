#include "Walnut/Application.h"

#include "Common.h"

#include "Helpers/Ngrok.h"

class NgrokHelperUI : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		static int protocol_type{};
		static int region{};
		static int port{};
		ImGui::InputInt("Port", &port);
		if (ImGui::Button("Create Tunnel"))
		{
			auto t = []()
				{
					Ngrok::CreateTunnel(protocol_type == 0 ? true : false, port, region);
				};
			std::thread(t).detach();
		}

		ImGui::SameLine();

		if (ImGui::Button("Close Tunnel"))
		{
			auto t = []()
				{
					Ngrok::CloseTunnel();
				};
			std::thread(t).detach();
		}

		ImGui::Separator();

		static std::string public_url{};
		ImGui::InputText("Public Url", &public_url);
		if (ImGui::Button("Get Public Url"))
		{
			auto t = []()
				{
					public_url = Ngrok::GetPublicURL();
				};
			std::thread(t).detach();
		}

		ImGui::SameLine();

		if (ImGui::Button("Copy Public Url"))
		{
			auto t = []()
				{
					Ngrok::CopyPublicURL();
				};
			std::thread(t).detach();
		}

		ImGui::Separator();

		static std::string authtoken{};
		ImGui::InputText("Authtoken", &authtoken);
		if (ImGui::Button("Set Authtoken"))
		{
			auto t = []()
				{
					std::system(fmt::format("ngrok config add-authtoken {}", authtoken).c_str());
				};
			std::thread(t).detach();
		}

		ImGui::Separator();

		ImGui::PushItemWidth(-1);
		ImGui::Combo("Region", &region, Ngrok::Regions, IM_ARRAYSIZE(Ngrok::Regions));
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(-1);
		ImGui::Combo("Protocol Type", &protocol_type, Ngrok::ProtocolType, IM_ARRAYSIZE(Ngrok::ProtocolType));
		ImGui::PopItemWidth();

		ImGui::Separator();

		if (ImGui::Button("Download Ngrok"))
		{
			auto t = []()
				{
					Util::DownloadFile(fmt::format("https://github.com/gnireorb/ngrok-helper/releases/download/{}/ngrok.exe", Ngrok::Version).c_str(), "ngrok.exe");
				};
			std::thread(t).detach();
		}
	}
};