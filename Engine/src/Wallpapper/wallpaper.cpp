#include "wallpaper.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <thread>

#include <sstream>

#include "../Render/Renderer.h"
#include "../Render/GL/render_GL.h"
#include <conio.h>
#include "../Image/Image.h"
//MODULES
#include "WPScan.h"
#include "Ripps.h"
namespace Everith {
	Wallpaper::Wallpaper() {}
	Wallpaper::~Wallpaper() {}

	void Wallpaper::SortRips()
	{
		Rips r;
		r.RipsSort();
	}
	void Wallpaper::rate_wallpappers() {
		Rips r;
		r.rate_wallpappers();
	}

	void Wallpaper::setTags(std::wstring info) {
		int switch_on = 0;
		std::vector<std::wstring> tags;

		//TODO time.cpp és time.h ban idö és random szám

		//if (info == "000") tags.insert (tags.end (), { "fekete", "anime",    "sfw" });     //   FEKETE   ANIME   SFW
		//if (info == "001") tags.insert (tags.end (), { "színes", "anime",    "sfw" });     //   SZINES   ANIME   SFW
		//if (info == "002") tags.insert (tags.end (), { "fehér",  "anime",    "sfw" });     //   FEHÉR    ANIME   SFW
		//if (info == "003") tags.insert (tags.end (), { "fekete", "anime",    "ecchi" });   //   FEKETE   ANIME   ECCHI
		//if (info == "004") tags.insert (tags.end (), { "színes", "anime",    "ecchi" });   //   SZINES   ANIME   ECCHI
		//if (info == "005") tags.insert (tags.end (), { "fehér",  "anime",    "ecchi" });   //   FEHÉR    ANIME   ECCHI
		//if (info == "006") tags.insert (tags.end (), { "fekete", "anime",    "nsfw" });    //   FEKETE   ANIME   HENTAI
		//if (info == "007") tags.insert (tags.end (), { "színes", "anime",    "nsfw" });    //   SZINES   ANIME   HENTAI
		//if (info == "008") tags.insert (tags.end (), { "fehér",  "anime",    "nsfw" });    //   FEHÉR    ANIME   HENTAI
		//if (info == "009") tags.insert (tags.end (), {}); //   -        -       -

		if (info == L"000") tags.insert(tags.end(), { L"\\0\\" });     //   FEKETE   ANIME   SFW
		if (info == L"001") tags.insert(tags.end(), { L"\\1\\" });     //   SZINES   ANIME   SFW
		if (info == L"002") tags.insert(tags.end(), { L"\\1\\" });     //   FEHÉR    ANIME   SFW
		if (info == L"003") tags.insert(tags.end(), { L"\\3\\" });   //   FEKETE   ANIME   ECCHI
		if (info == L"004") tags.insert(tags.end(), { L"\\4\\" });   //   SZINES   ANIME   ECCHI
		if (info == L"005") tags.insert(tags.end(), { L"\\5\\" });   //   FEHÉR    ANIME   ECCHI
		if (info == L"006") tags.insert(tags.end(), { L"\\6\\" });    //   FEKETE   ANIME   HENTAI
		if (info == L"007") tags.insert(tags.end(), { L"\\7\\" });    //   SZINES   ANIME   HENTAI
		if (info == L"008") tags.insert(tags.end(), { L"\\7\\" });    //   FEHÉR    ANIME   HENTAI
		if (info == L"009") tags.insert(tags.end(), { L"\\9\\" }); //   -        -       -

		//Log::Report (tags[0].c_str (), tags[1].c_str (), tags[2].c_str ());

		Wallpaper_Set(tags);
	}
	//marad itt
	void Wallpaper::Wallpaper_Set(std::vector<std::wstring> tags) {
		int index = 0;
		std::wstring path;
		std::vector < Wallpaper_data> wall_data;

		Wallpaper_data_load(&wall_data, tags);
		srand(time(NULL));
		index = (rand() % wall_data.size());
		path = wall_data[index].path + wall_data[index].name;
		//l.Report (path.c_str ());
		if (!(SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)path.c_str(), SPIF_UPDATEINIFILE))) {
			//l.Error ("Nem található képfáj");
			system("pause");
		}
	}
	void Wallpaper::Wallpaper_data_load(std::vector <Wallpaper_data>* wall_data, std::vector<std::wstring> tags) {
		std::wifstream stream("Data\\Wallpaper_data.txt");
		std::wstring line;
		int watcher = 0;

		std::wstring path;
		std::wstring name;
		std::wstring size;
		std::wstring width;
		std::wstring height;

		while (getline(stream, line)) {
			for (std::wstring& tag : tags) {
				if (line.find(tag) != std::wstring::npos) {
					watcher = 1;
				}
				else {
					watcher = -1;
				}
				if (watcher == 1) {
					stream >> path;
					stream >> name;
					stream >> size;
					stream >> width;
					stream >> height;

					wall_data->push_back({ path, name, stoi(size), stoi(width), stoi(height) });
				}
			}
		}
		stream.close();
	}

	//scan
	void Wallpaper::wallpaper_update() {
		Config c;
		std::wstring wpPath = c.conf(L"wallpaper_path");
		std::wstring NSFW[] = {
			wpPath + L"\\0\\",
			wpPath + L"\\4\\",
			wpPath + L"\\5\\",
			wpPath + L"\\6\\",
			wpPath + L"\\7\\",
			wpPath + L"\\8\\",
			wpPath + L"\\9\\"
		};
		std::vector<std::wstring> SFW = {
			wpPath + L"\\1\\",
			wpPath + L"\\2\\",
			wpPath + L"\\3\\"
		};

		std::wofstream wall_out("Data\\Wallpaper_data.txt");
		if (!wall_out.is_open()) {
			throw std::runtime_error("Failed to open file!");
		}
		wall_out.close();

		for (std::wstring& path : NSFW) {
			Wallpaper_data_update(path);
		}
		for (std::wstring& path : SFW) {
			Wallpaper_data_update(path);
		}
	}

	void Wallpaper::Wallpaper_data_update(std::wstring path) {
		HANDLE hFind;
		WIN32_FIND_DATA data;
		std::wstring pathx = path + L"*";
		std::wstring path_res;
		std::wstring tempName;
		int Height = 0;
		int Width = 0;
		hFind = FindFirstFile(pathx.c_str(), &data);
		if (hFind != INVALID_HANDLE_VALUE) {
			std::wofstream wall_out("Data\\Wallpaper_data.txt", std::wofstream::app);
			if (!wall_out.is_open()) {
				throw std::runtime_error("Failed to open file!");
			}
			while (FindNextFile(hFind, &data)) {
				tempName = data.cFileName;
				if (tempName != L"..") {
					path_res = path + data.cFileName;
#ifdef DEBUG
					//l.Report ((path + "\\" + tempName).c_str ());
#endif
					wall_out << path << L" " << data.cFileName << L" " << data.nFileSizeLow << L" " << Height << L" " << Width << L"\n";
				}
			}
			wall_out.close();
			FindClose(hFind);
		}
	}

	void Wallpaper::sort_wallpaper() {
		WPScan scan(L"D:\\rips");
		scan.Scan();
		sort_files(scan.getWPDL());
	}

	void Wallpaper::sort_files(std::vector<Wallpaper_data> lista) {
		std::wstring newPathDesktop = L"D:\\Pictures\\háttérképek_válogatás\\desktop\\";
		std::wstring newPathMobile = L"D:\\Pictures\\háttérképek_válogatás\\mobile\\";
		double Desktop = 1920.0 / 1080.0;
		double Moblie = 1080.0 / 1920.0;
		double image_arany_x = 0.0;
		double image_arany_y = 0.0;
		double image_arany = 0.0;
		int i = 0;
		time_t t;
		time(&t);
		std::wstring time = std::to_wstring(t);

		for (i = 0; i < lista.size(); i++) {
			image_arany_x = 0.0;
			image_arany_y = 0.0;

			image_arany_x += lista[i].width;
			image_arany_y += lista[i].heigth;
			image_arany = image_arany_x / image_arany_y;

			//DESKTOP
			if (lista[i].width >= 1800) {
				if (image_arany >= Desktop - 0.1 && image_arany <= Desktop + 0.1) {
					if (lista[i].name.find(L".jpg") != std::string::npos) {
						//rename ((lista[i].path + lista[i].name).c_str (), (newPathDesktop + std::to_string (i) + time + ".jpg").c_str ());
					}
					if (lista[i].name.find(L".png") != std::string::npos) {
						//rename ((lista[i].path + lista[i].name).c_str (), (newPathDesktop + std::to_string (i) + time + ".png").c_str ());
					}
					//MoveFile ((lista[i].path + "\\" + lista[i].name).c_str (), (newPathDesktop + lista[i].name).c_str ());
					//std::cout << "Desktop: " << (newPathDesktop + lista[i].name).c_str () << std::endl;
				}
			}
			//MOBILE
			if (lista[i].width >= 900) {
				if (image_arany >= Moblie - 0.1 && image_arany <= Moblie + 0.1) {
					if (lista[i].name.find(L".jpg") != std::string::npos) {
						//rename ((lista[i].path + lista[i].name).c_str (), (newPathMobile + std::to_string (i) + ".jpg").c_str ());
					}
					if (lista[i].name.find(L".png") != std::string::npos) {
						//rename ((lista[i].path + lista[i].name).c_str (), (newPathMobile + std::to_string (i) + ".png").c_str ());
					}
					//MoveFile ((lista[i].path + "\\" + lista[i].name).c_str (), (newPathMobile + lista[i].name).c_str ());
					//std::cout << "Mobile: " << (newPathMobile + lista[i].name).c_str () << std::endl;
				}
			}
		}
	}

	//int m_key;
	//void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
	//{
	//    if (action)
	//    {
	//        Wallpaper w;
	//        m_key = key;
	//    }
	//}

	//bool Wallpaper::WallpaperEvent (Wallpaper_data image) {
	//    std::string Desktop = "D:\\Pictures\\Hátérképek\\";
	//    std::string Mobile = "D:\\Pictures\\Mobile\\";
	//    double arany = 1920.0 / 1080.0;
	//    double aranyMobile = 1080.0 / 1920.0;
	//    double imArany = (double)image.heigth / (double)image.width;

	//    std::cout << m_key << std::endl;
	//    switch (m_key)
	//    {
	//    case '0':
	//    case '`':
	//    case GLFW_KEY_KP_DECIMAL:
	//        l.Report ("Deleting: ", (image.path + image.name).c_str ());
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\háttérképek_válogatás\\Remove\\" + image.name).c_str ());
	//        break;
	//    case '1':
	//    case GLFW_KEY_KP_1:
	//        l.Report ((image.path + image.name).c_str ());
	//        l.Report ("1");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "1\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "Anime\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "1\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '2':
	//    case GLFW_KEY_KP_2:
	//        l.Report (image.path.c_str ());
	//        l.Report ("2");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "2\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "1\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "2\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '3':
	//    case GLFW_KEY_KP_3:
	//        l.Report (image.path.c_str ());
	//        l.Report ("3");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "3\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "Anime\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "3\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '4':
	//    case GLFW_KEY_KP_4:
	//        l.Report (image.path.c_str ());
	//        l.Report ("4");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "4\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "2\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "4\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '5':
	//    case GLFW_KEY_KP_5:
	//        l.Report (image.path.c_str ());
	//        l.Report ("5");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "5\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "2\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "5\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '6':
	//    case GLFW_KEY_KP_6:
	//        l.Report (image.path.c_str ());
	//        l.Report ("6");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "6\\" + image.name).c_str ());
	//            l.Report ("Desktop:");
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "Anime\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "6\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '7':
	//    case GLFW_KEY_KP_7:
	//        l.Report (image.path.c_str ());
	//        l.Report ("7");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "7\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "3\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "7\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '8':
	//    case GLFW_KEY_KP_8:
	//        l.Report (image.path.c_str ());
	//        l.Report ("8");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "8\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "3\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "8\\" + image.name).c_str ());
	//        }
	//        break;
	//    case '9':
	//    case GLFW_KEY_KP_9:
	//        l.Report (image.path.c_str ());
	//        l.Report ("9");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "9\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "H\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "9\\" + image.name).c_str ());
	//        }
	//        break;
	//    case GLFW_KEY_KP_0:
	//        l.Report (image.path.c_str ());
	//        l.Report ("0");
	//        if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "0\\" + image.name).c_str ());
	//        }
	//        else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
	//            l.Report ("Mobile:");
	//            MoveFile ((image.path + image.name).c_str (), (Mobile + "0\\" + image.name).c_str ());
	//        }
	//        else
	//        {
	//            l.Report ("Desktop:");
	//            MoveFile ((image.path + image.name).c_str (), (Desktop + "0\\" + image.name).c_str ());
	//        }
	//        break;
	//    case 'E':
	//        l.Report ("Egész test");
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\Models\\egesz_test\\" + image.name).c_str ());
	//        break;
	//    case 'A':
	//        l.Report ("Alsó test");
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\Models\\also\\" + image.name).c_str ());
	//        break;
	//    case 'F':
	//        l.Report ("Felső test");
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\Models\\felso\\" + image.name).c_str ());
	//        break;
	//    case 'W':
	//        l.Report ("Fej");
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\Models\\fej\\" + image.name).c_str ());
	//        break;
	//    case 'S':
	//        l.Report ("Szerv");
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\Models\\szerv\\" + image.name).c_str ());
	//        break;
	//    case 'R':
	//        l.Report ("Ruah kevés");
	//        MoveFile ((image.path + image.name).c_str (), ("D:\\Pictures\\Models\\ruha_keves\\" + image.name).c_str ());
	//        break;
	//    default:
	//        l.Report ("Default / Warning: A lehetöszégek 0 és 9 között vannak! ");
	//        l.Report ("Model: -----------");
	//        l.Report ("Egész test: e");
	//        l.Report ("Alsó: a");
	//        l.Report ("Felső: f");
	//        l.Report ("Fej: w");
	//        l.Report ("Szerv: s");
	//        l.Report ("Kevés Ruha: r");
	//        return 0;
	//        break;
	//    }
	//    return 1;
	//}
}