#include "Ripps.h"

#include <windows.h>
#include <thread>

#include "..\Image\Image.h"
#include "../Render/Renderer.h"
#include "../Render/GL/render_GL.h"
#include "WPScan.h"
#include "..\Audio\Audio.h"

//CONVERTER
#include <locale>
#include <codecvt>
//################

namespace Everith {
	Rips::Rips()
	{
	}
	Rips::~Rips()
	{
	}

	int m_key;
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action)
		{
			Wallpaper w;
			m_key = key;
		}
	}
	void Rips::RipsSort()
	{
		//RENDERER
		Renderer r;
		GLFWwindow* WindowID = r.getWindowID();
		Image img;
		bool done = false;

		r.DrawImage1(L"D:\\Everith\\Data\\Images\\logo.png", 32 * 3, 32 * 3);

		std::thread thread1(&Rips::LoadRiper, this);
		while (!m_isdone)
		{
			Sleep(500);
		}
		Sleep(500);

		m_key = 0;
		m_WP = false;
		while (!glfwWindowShouldClose(WindowID) && !done)
		{
			glfwSetKeyCallback(WindowID, key_callback);
			r.DrawImage1((m_WPDL[index].path + m_WPDL[index].name).c_str(), m_WPDL[index].width, m_WPDL[index].heigth);

			m_WPD = m_WPDL[index];
			if (!m_WP)
			{
				isWallpaper();
			}
			if (m_key)
			{
				if (Events(m_key))
				{
					index++;
				}
			}
			m_key = 0;
			if (index >= m_WPDL.size()) done = true;
		}
		thread1.detach();
#ifdef DEBUG
		l.Report("Lista válogatott: ", m_WPDL.size());
#endif
	}
	void Rips::isWallpaper()
	{
		double arany = 1920.0f / 1080.0f;
		double aranyMobile = 1080.0f / 1920.0f;
		double tures = 0.1f;
		double imArany = (double)m_WPD.width / (double)m_WPD.heigth;
		if (imArany <= arany + tures && imArany >= arany - tures && m_WPD.width >= 1920 * 0.9 && m_WPD.heigth >= 1080 * 0.9)
		{
			Sound::playWAV(L"D:\\Everith\\Data\\soft-hitwhistle.wav");
			m_WP = true;
		}
		else if (imArany <= aranyMobile + tures && imArany >= aranyMobile - tures && m_WPD.heigth >= 1920 * 0.9 && m_WPD.width >= 1080 * 0.9) {
			Sound::playWAV(L"D:\\Everith\\Data\\soft-hitwhistle.wav");
			m_WP = true;
		}
	}
	bool Rips::Events(int event)
	{
		switch (m_key)
		{
		case '0':
		case '`':
		case GLFW_KEY_KP_DECIMAL:
			l.Error("Deleting: "/*, (m_WPD.path + m_WPD.name).c_str ()*/);
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Remove\\" + m_WPD.name).c_str());
			m_WPDL[index].path = L"D:\\Pictures\\Remove\\";
			m_WP = false;
			//remove ((m_WPD.path + m_WPD.name).c_str);
			break;

		case '1':
		case GLFW_KEY_KP_1:
			EventAction(L"1", L"1", L"1");
			break;
		case '2':
		case GLFW_KEY_KP_2:
			EventAction(L"2", L"1", L"1");
			break;
		case '3':
		case GLFW_KEY_KP_3:
			EventAction(L"3", L"1", L"1");
			break;
		case '4':
		case GLFW_KEY_KP_4:
			EventAction(L"4", L"2", L"2");
			break;
		case '5':
		case GLFW_KEY_KP_5:
			EventAction(L"5", L"2", L"2");
			break;
		case '6':
		case GLFW_KEY_KP_6:
			EventAction(L"6", L"Anime", L"2");
			break;
		case '7':
		case GLFW_KEY_KP_7:
			EventAction(L"7", L"3", L"specia");
			break;
		case '8':
		case GLFW_KEY_KP_8:
			EventAction(L"8", L"3", L"3");
			break;
		case '9':
		case GLFW_KEY_KP_9:
			EventAction(L"9", L"H", L"3");
			break;
		case GLFW_KEY_KP_0:
			EventAction(L"0", L"0", L"0");
			break;
		case 'E':
			l.Report("Egész test");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\whole-body\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'A':
			l.Report("Alsó test");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\lower-body\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'Q':
			l.Report("Felső test");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\upper-body\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'D':
			l.Report("Head");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\Head\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'S':
			l.Report("pussy");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\pussy\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'W':
			l.Report("breast");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\breast\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'R':
			l.Report("Ruah kevés");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\cloth\\ruha_keves\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'B':
			l.Report("Bwosette");
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Browsette\\" + m_WPD.name).c_str());
			m_WP = false;
			break;
		case 'U':
		case GLFW_KEY_BACKSPACE:
			l.Pass("Vissza "/*, (m_WPDL[index - 1].name).c_str ()*/);
			MoveFileW((L"D:\\Pictures\\Remove\\" + m_WPDL[index - 1].name).c_str(), (m_WPDL[index - 1].path + m_WPDL[index - 1].name).c_str());
			index--;
			index--;
			m_WP = false;
			break;
		default:
			l.Report("Default / Warning: A lehetöszégek 0 és 9 között vannak! ");
			l.Report("Model: -----------");
			l.Report("Egész test: e");
			l.Report("Alsó: a");
			l.Report("Felső: q");
			l.Report("Head: d");
			l.Report("pussy: s");
			l.Report("breast: w");
			l.Report("Kevés Ruha: r");
			l.Report("Bwosette: b");
			l.Report("Recover last: u / backspace");
			return 0;
			break; (m_WPD.path + m_WPD.name).c_str();
		}
		return 1;
	}
	void Rips::EventAction(std::wstring Desk, std::wstring Mobil, std::wstring good)
	{
		std::wstring Desktop = L"D:\\Pictures\\Hátérképek\\";
		std::wstring Mobile = L"D:\\Pictures\\Mobile\\";
		std::wstring Rips = L"D:\\Pictures\\good\\";
		double arany = 1920.0f / 1080.0f;
		double aranyMobile = 1080.0f / 1920.0f;
		double tures = 0.1f;
		double imArany = (double)m_WPD.width / (double)m_WPD.heigth;
#ifdef DEBUG
		int xtest = 1920 * 0.9;
#endif // DEBUG
		//CONVERTER
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string path_str = converter.to_bytes(m_WPD.path + m_WPD.name).c_str();

		if (imArany <= arany + tures && imArany >= arany - tures && m_WPD.width >= 1920 * 0.9 && m_WPD.heigth >= 1080 * 0.9) {
			l.Report("Desktop: ", path_str.c_str());
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (Desktop + Desk + L"\\" + m_WPD.name).c_str());
			m_WPDL[index].path = Desktop + Desk + L"\\";
		}
		else if (imArany <= aranyMobile + tures && imArany >= aranyMobile - tures && m_WPD.heigth >= 1920 * 0.9 && m_WPD.width >= 1080 * 0.9) {
			l.Report("Mobile: ", path_str.c_str());
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (Mobile + Mobil + L"\\" + m_WPD.name).c_str());
			m_WPDL[index].path = Mobile + Mobil + L"\\";
		}
		else
		{
			l.Report("Rips: ", path_str.c_str());
			MoveFileW((m_WPD.path + m_WPD.name).c_str(), (Rips + good + L"\\" + m_WPD.name).c_str());
			m_WPDL[index].path = Rips + good + L"\\";
		}
		m_WP = false;
	}
	void Rips::LoadRiper()
	{
		WPScan scan(L"D:\\rips");
		l.Report("D:\\rips");
		scan.RiperScan(m_WPDL, m_isdone);
	}

	//Rate WP from valgatasok
	void Rips::rate_wallpappers() {
		Image img;

		std::vector<Wallpaper_data> listaIMAGES;
		std::vector<Wallpaper_data> listaIMAGES1;
		std::wstring pathDesktop = L"D:\\rips\\valogatni\\desktop";
		std::wstring pathMobile = L"D:\\rips\\valogatni\\mobile";
		WPScan scanD(pathDesktop);
		WPScan scanM(pathMobile);

#ifdef DEBUG
		//l.Report (pathDesktop.c_str ());
		//l.Report (pathMobile.c_str ());
#endif // DEBUG

		listaIMAGES = scanD.getWPDL();
		listaIMAGES1 = scanM.getWPDL();
		for (size_t i = 0 (); i < listaIMAGES1.size(); i++)
		{
			listaIMAGES.push_back({ listaIMAGES1[i].path ,listaIMAGES1[i].name ,listaIMAGES1[i].width ,listaIMAGES1[i].heigth ,listaIMAGES1[i].meret });
		}

#ifdef DEBUG
		listaIMAGES.insert(listaIMAGES.end(), std::make_move_iterator(listaIMAGES1.begin()), std::make_move_iterator(listaIMAGES1.end()));
		l.Report("Lista válogatott: ", listaIMAGES.size());
#endif // DEBUG

		int index = 0;
		bool done = false;
		//RENDERER
		Renderer r;
		GLFWwindow* WindowID = r.getWindowID();

		m_key = 0;
		while (!glfwWindowShouldClose(WindowID) && !done)
		{
			//TODO key_callback INPUT EVENT handler
			glfwSetKeyCallback(WindowID, key_callback);
			r.DrawImage((listaIMAGES[index].path + listaIMAGES[index].name).c_str(), listaIMAGES[index].width, listaIMAGES[index].heigth);
			if (m_key)
			{
				if (WallpaperEvent(listaIMAGES[index]))
				{
					index++;
				}
			}
			m_key = 0;
			if (index >= listaIMAGES.size()) done = true;
		}
	}
	bool Rips::WallpaperEvent(Wallpaper_data image) {
		std::wstring Desktop = L"D:\\Pictures\\Hátérképek\\";
		std::wstring Mobile = L"D:\\Pictures\\Mobile\\";
		double arany = 1920.0 / 1080.0;
		double aranyMobile = 1080.0 / 1920.0;
		double imArany = (double)image.width / (double)image.heigth;

		std::cout << m_key << std::endl;
		switch (m_key)
		{
		case '0':
		case '`':
		case GLFW_KEY_KP_DECIMAL:
			l.Report("Deleting: "/*, (image.path + image.name).c_str ()*/);
			MoveFileW((image.path + image.name).c_str(), (L"D:\\Pictures\\Remove\\" + image.name).c_str());
			break;
		case '1':
		case GLFW_KEY_KP_1:
			//l.Report ((image.path + image.name).c_str ());
			l.Report("1");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFileW((image.path + image.name).c_str(), (Desktop + L"1\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFileW((image.path + image.name).c_str(), (Mobile + L"Anime\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFileW((image.path + image.name).c_str(), (Desktop + L"1\\" + image.name).c_str());
			}
			break;
		case '2':
		case GLFW_KEY_KP_2:
			//l.Report (image.path.c_str ());
			l.Report("2");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFileW((image.path + image.name).c_str(), (Desktop + L"2\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFileW((image.path + image.name).c_str(), (Mobile + L"1\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"2\\" + image.name).c_str());
			}
			break;
		case '3':
		case GLFW_KEY_KP_3:
			//l.Report (image.path.c_str ());
			l.Report("3");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"3\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"Anime\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"3\\" + image.name).c_str());
			}
			break;
		case '4':
		case GLFW_KEY_KP_4:
			//l.Report (image.path.c_str ());
			l.Report("4");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"4\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"2\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"4\\" + image.name).c_str());
			}
			break;
		case '5':
		case GLFW_KEY_KP_5:
			//l.Report (image.path.c_str ());
			l.Report("5");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"5\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"2\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"5\\" + image.name).c_str());
			}
			break;
		case '6':
		case GLFW_KEY_KP_6:
			//l.Report (image.path.c_str ());
			l.Report("6");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				MoveFile((image.path + image.name).c_str(), (Desktop + L"6\\" + image.name).c_str());
				l.Report("Desktop:");
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"Anime\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"6\\" + image.name).c_str());
			}
			break;
		case '7':
		case GLFW_KEY_KP_7:
			//l.Report (image.path.c_str() );
			l.Report("7");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"7\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"3\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"7\\" + image.name).c_str());
			}
			break;
		case '8':
		case GLFW_KEY_KP_8:
			//l.Report (image.path.c_str ());
			l.Report("8");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"8\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"3\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"8\\" + image.name).c_str());
			}
			break;
		case '9':
		case GLFW_KEY_KP_9:
			//l.Report (image.path.c_str ());
			l.Report("9");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"9\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"H\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"9\\" + image.name).c_str());
			}
			break;
		case GLFW_KEY_KP_0:
			//l.Report (image.path.c_str ());
			l.Report("0");
			if (imArany <= arany + 0.1 && imArany >= arany - 0.1) {
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"0\\" + image.name).c_str());
			}
			else if (imArany <= aranyMobile + 0.1 && imArany >= aranyMobile - 0.1) {
				l.Report("Mobile:");
				MoveFile((image.path + image.name).c_str(), (Mobile + L"0\\" + image.name).c_str());
			}
			else
			{
				l.Report("Desktop:");
				MoveFile((image.path + image.name).c_str(), (Desktop + L"0\\" + image.name).c_str());
			}
			break;
		case 'E':
			l.Report("Egész test");
			MoveFile((image.path + image.name).c_str(), (L"D:\\Pictures\\Models\\whole-body\\" + image.name).c_str());
			break;
		case 'A':
			l.Report("Alsó test");
			MoveFile((image.path + image.name).c_str(), (L"D:\\Pictures\\Models\\lower-body\\" + image.name).c_str());
			break;
		case 'Q':
			l.Report("Felső test");
			MoveFile((image.path + image.name).c_str(), (L"D:\\Pictures\\Models\\upper-body\\" + image.name).c_str());
			break;
		case 'D':
			l.Report("Head");
			MoveFile((image.path + image.name).c_str(), (L"D:\\Pictures\\Models\\Head\\" + image.name).c_str());
			break;
		case 'S':
			l.Report("pussy");
			MoveFile((image.path + image.name).c_str(), (L"D:\\Pictures\\Models\\pussy\\" + image.name).c_str());
			break;
		case 'R':
			l.Report("Ruah kevés");
			MoveFile((image.path + image.name).c_str(), (L"D:\\Pictures\\Models\\ruha_keves\\" + image.name).c_str());
			break;
		case 'W':
			l.Report("breast");
			MoveFile((m_WPD.path + m_WPD.name).c_str(), (L"D:\\Pictures\\Models\\breast\\" + m_WPD.name).c_str());
			break;
		default:
			l.Report("Default / Warning: A lehetöszégek 0 és 9 között vannak! ");
			l.Report("Model: -----------");
			l.Report("Egész test: e");
			l.Report("Alsó: a");
			l.Report("Felső: f");
			l.Report("Head: w");
			l.Report("pussy: s");
			l.Report("Kevés Ruha: r");
			return 0;
			break;
		}
		return 1;
	}
}