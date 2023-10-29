#pragma once
#include "Common.h"

class Settings {
public:
	explicit Settings() = default;
	~Settings() = default;

	int TimesSaved{};

	nlohmann::json Options;
	nlohmann::json DefaultOptions =
		R"({
			"Bool": true,
			"String": "std::string",
			"Float": 1337.0,
            "Integer": 1337,
			"Combo": 0,
			"Radio": 0,
			"Byte": 255
		})"_json;

	bool Save()
	{
		std::string SettingsFile = std::filesystem::current_path().string();
		SettingsFile += "\\Settings.json";

		std::ofstream File(SettingsFile, std::ios::out | std::ios::trunc);
		File << Options.dump(4);
		File.close();
		return true;
	}

	bool Load()
	{
		std::string SettingsFile = std::filesystem::current_path().string();
		SettingsFile += "\\Settings.json";

		std::ifstream File(SettingsFile);

		if (!File.is_open())
		{
			WriteDefaultConfig();
			File.open(SettingsFile);
		}

		File >> Options;

		bool ShouldSave = false;
		for (auto& e : DefaultOptions.items())
		{
			if (Options.count(e.key()) == 0)
			{
				ShouldSave = true;
				Options[e.key()] = e.value();
			}

		}

		if (ShouldSave)
		{
			TimesSaved += 1;
			Save();
		}

		return true;
	}
private:
	bool WriteDefaultConfig()
	{
		std::string SettingsFile = std::filesystem::current_path().string();
		SettingsFile += "\\Settings.json";

		std::ofstream File(SettingsFile, std::ios::out);
		File << DefaultOptions.dump(4);
		File.close();

		Options.clear();
		Options = DefaultOptions;

		return true;
	}
};

inline Settings g_Settings;
