#include "HTTPRequest.hpp"

#include "Common.h"
#include "Util.h"

namespace Ngrok
{
	static const char* const Version{ "v1.7" };
	static const char* const Regions[]{ "South America", "North America", "Europe", "Asia", "Australia" };
	static const char* const ProtocolType[]{ "TCP", "HTTP" };

	static bool CreateTunnel(bool tcp, int port, int region)
	{
		auto ngrok_tcp = [](bool is_tcp, int port, const char* region)
		{
			auto _system = [](bool is_tcp, int port, const char* region)
			{
				std::system(fmt::format("ngrok {} {} --region {}", is_tcp ? "tcp" : "http", port, region).c_str());
			};
			std::thread(_system, is_tcp, port, region).detach();
		};

		if (region >= 4 || region < 0)
			return false;

		switch (region)
		{
		case 0:
			ngrok_tcp(tcp, port, "sa");
			break;
		case 1:
			ngrok_tcp(tcp, port, "us");
			break;
		case 2:
			ngrok_tcp(tcp, port, "eu");
			break;
		case 3:
			ngrok_tcp(tcp, port, "ap");
			break;
		case 4:
			ngrok_tcp(tcp, port, "au");
			break;
		}

		return true;
	}

	// shit ass dumb way, but works.
	static void CloseTunnel()
	{
		std::system("taskkill /f /im ngrok.exe");
	}

	static const char* GetPublicURL()
	{
		http::Request request("http://127.0.0.1:4040/api/tunnels");
		const auto response = request.send("GET");
		const auto json = nlohmann::json::parse(std::string{ response.body.begin(), response.body.end() });
		for (auto& tunnels : json["tunnels"])
		{
			return tunnels["public_url"].get<std::string>().erase(0, 6).c_str();
		}
		return ("Undefined");
	}

	static void CopyPublicURL()
	{
		http::Request request("http://127.0.0.1:4040/api/tunnels");
		const auto response = request.send("GET");
		const auto json = nlohmann::json::parse(std::string{ response.body.begin(), response.body.end() });
		for (auto& tunnels : json["tunnels"])
		{
			Util::ToClipboard(tunnels["public_url"].get<std::string>().erase(0, 6).c_str());
		}
		Util::ToClipboard("undefined");
	}
}