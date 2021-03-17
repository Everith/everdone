#include "config.h"

namespace Everith {
	Config::Config()
	{
	}
	Config::~Config()
	{
	}
	void Config::check()
	{
		std::wifstream config_in("Data\\config.txt", std::ios::binary);
		if (!config_in.is_open()) {
			EVE_CORE_INFO("Config file creation:");
			std::wofstream config_out("D:\\Everith\\Data\\config.txt");
			if (!config_out.is_open()) {
				throw std::runtime_error("Failed to open file!");
			}
			config_out << L"Version: 0.1\n";
			config_out << L"sort_mobile: D:\\Pictures\\háttérképek_válogatás\\mobile \n";
			config_out << L"sort_desktop: D:\\Pictures\\háttérképek_válogatás\\desktop \n";
			config_out << L"sort_dir: D:\\rips \n";
			config_out << L"wallpaper_path: D:\\Dropbox\\Kpek\\Htrkpek \n";
			config_out.close();
			EVE_CORE_INFO("New Config created!");
		}
		else {
			EVE_CORE_INFO("Config alredy exist!");
		}
		EVE_CORE_INFO("Config setup succesful.");
	}

	std::string Config::conf(std::string name)
	{
		//Read confog
		std::string line;
		std::string result;
		std::ifstream config_in("Data\\config.txt", std::ios::binary);
		if (!config_in.is_open()) {
			throw std::runtime_error("Failed to open file!");
		}
		while (getline(config_in, line)) {
			if (!line.find(name)) {
				for (size_t i = name.length() + 2; i < line.length() - 1; i++) {
					result += line[i];
				}
				//TODO lehet itt lesz a return
			}
		}
		config_in.close();
		return result;
	}
}