#include "WPScan.h"

#include <windows.h>
#include <thread>
#include <sstream>
#include <string>
#include <fstream>

#include "Struct/WallpaperData.h"
#include "..\File\Mappa.h"
#include "..\Image\Image.h"
#include <algorithm>
#include <iterator>

#include <objidl.h>
//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment (lib,"Gdiplus.lib")
#include <codecvt>

#include <stdio.h>

#ifdef DEBUG
#include <time.h>
#endif // DEBUG

namespace Everith {
	WPScan::WPScan(std::wstring path)
	{
		m_path = path;
	}

	WPScan::~WPScan()
	{
	}
	void WPScan::Scan() {
		//LoadSaveFile ();
		initScan();
		GetSize();
		MegreLists();
		Save();
	}
	void WPScan::GetSizeRiper(std::vector<Wallpaper_data>& WPDL)
	{
		//Image img;
		//int Height = 0;
		//int Width = 0;

		//Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		//ULONG_PTR gdiplusToken;
		//GdiplusStartup (&gdiplusToken, &gdiplusStartupInput, NULL);
		//UINT    size = 0;
		//UINT    count = 0;

		//std::wstring ws;
		//Gdiplus::RectF boundsRect;
		//Gdiplus::Unit unit;
		//int x, y;
		//for (int i = 0; i < m_TWPDL.size (); i++) {
		//    ws = m_TWPDL[i].path + m_TWPDL[i].name;
		//    //std::wstring ws (s.begin (), s.end ());
		//    Gdiplus::Image image (ws.c_str ());
		//    image.GetBounds (&boundsRect, &unit);
		//    x = boundsRect.Width;
		//    y = boundsRect.Height;
		//    WPDL.push_back ({ m_TWPDL[i].path, m_TWPDL[i].name, x, y });
		//}
		//Gdiplus::GdiplusShutdown (gdiplusToken);
	}

	void WPScan::LoadSaveFile()
	{
		std::wifstream fs("Data\\Images\\ImageSizes.txt", std::ios::binary);
		std::wstring ws;
		while (getline(fs, ws))
		{
			m_FS << ws;
#ifdef DEBUG
			std::wcout << ws.c_str() << std::endl;
#endif // DEBUG
		}
		fs.close();
	}

	bool WPScan::isExist(std::wstring search) {
		std::wstring ws;
		m_FS.clear();
		m_FS.seekg(0, std::ios::beg);

		while (std::getline(m_FS, ws))
		{
			if (ws.find(search, 0) != std::wstring::npos) {
#ifdef DEBUG
				//l.Pass ("Found: ", search.c_str ());
#endif // DEBUG
				return 1;
			}
			else
			{
#ifdef DEBUG
				//l.Error ("Not Found: ", search.c_str ());
#endif // DEBUG
				return 0;
			}
		}
		return 0;
	}

	bool WPScan::initScan() {
		std::vector<std::wstring> paths;

		ScanFiles(paths, m_path);
		for (int i = 0; i < paths.size(); i++)
		{
			ScanFiles(paths, paths[i]);
		}
		return true;
#ifdef DEBUG
		std::cout << "Osszes kép méretnélkul: " << m_TWPDL.size() << std::endl;
#endif // DEBUG
	}

	void WPScan::RiperScan(std::vector<Wallpaper_data>& WPDL, bool& isdone)
	{
		isdone = initScan();
#ifdef DEBUG
		l.Pass("DONE RIPPER LIST UPDATE");
#endif // DEBUG
		GetSizeRiper(WPDL);
	}

	void WPScan::Save()
	{
		std::wofstream sf("Data\\Images\\ImageSizes.txt", std::wofstream::out);
		if (!sf.is_open()) {
			throw std::runtime_error("Failed to open file!");
		}
		for (size_t i = 0; i < m_WPDL.size(); i++)
		{
			sf << m_WPDL[i].path.c_str() << L" " << m_WPDL[i].name.c_str() << L" " << m_WPDL[i].width << L" " << m_WPDL[i].heigth << L" " << m_WPDL[i].meret << L"\n";
		}
	}

	void WPScan::MegreLists()
	{
		for (size_t i = 0; i < m_TWPDL.size(); i++)
		{
			m_WPDL.push_back({ m_TWPDL[i].path, m_TWPDL[i].name, m_TWPDL[i].width, m_TWPDL[i].heigth, m_TWPDL[i].meret });
		}
	}

	void WPScan::ScanFiles(std::vector<std::wstring>& s, std::wstring path) {
		std::wstringstream ss;
		std::wstring word;

		mappa::FileNames(path, ss);

		ScanMappa(ss, word, s, path);
		ScanImage(ss, word, path);
	}

	void WPScan::ScanMappa(std::wstringstream& ss, std::wstring& word, std::vector<std::wstring>& s, std::wstring& path)
	{
		ss.clear();
		ss.seekg(0, std::ios::beg);
		while (std::getline(ss, word))
		{
			if (word.find(L".") == std::wstring::npos)
			{
				//std::cout << "Mappa: " << path << "\\" << word << std::endl;
				s.push_back(path + L"\\" + word);
			}
		}
	}

	void WPScan::ScanImage(std::wstringstream& ss, std::wstring& word, std::wstring& path)
	{
		ss.clear();
		ss.seekg(0, std::ios::beg);
		while (std::getline(ss, word))
		{
			if (word.find(L".png") != std::wstring::npos || word.find(L".jpg") != std::wstring::npos)
			{
				m_TWPDL.push_back({ path + L"\\", word });
			}

			//if (word.find (".png") != std::string::npos || word.find (".jpg") != std::string::npos)
			//{
			//    //std::cout << "Image: " << word << std::endl;
			//    if (isExist (path + "\\" + " " + word))
			//    {
			//        m_WPDL.push_back ({ path + "\\", word });
			//    }
			//    else
			//    {
			//        m_TWPDL.push_back ({ path + "\\", word });
			//    }
			//}
		}
	}

	void WPScan::GetSize() {
		int tempsize1 = m_TWPDL.size() / 4;
		std::thread thread1(&WPScan::GetSizeThread, this, 0, tempsize1);
		std::thread thread2(&WPScan::GetSizeThread, this, tempsize1, tempsize1 * 2);
		std::thread thread3(&WPScan::GetSizeThread, this, tempsize1 * 2, tempsize1 * 3);
		std::thread thread4(&WPScan::GetSizeThread, this, tempsize1 * 3, m_TWPDL.size());

		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
	}

	void WPScan::GetSizeThread(int startindex, int endindex)
	{
		Image img;
		int i = startindex;
		int Height = 0;
		int Width = 0;
#ifdef DEBUG
		int szamlalo = startindex;
		int t = clock();
		int elapsed;
#endif

		//using namespace Gdiplus;
		//Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		//ULONG_PTR gdiplusToken;
		//GdiplusStartup (&gdiplusToken, &gdiplusStartupInput, NULL);
		//UINT    size = 0;
		//UINT    count = 0;

		//std::wstring ws;
		//Gdiplus::RectF boundsRect;
		//Gdiplus::Unit unit;

		for (i = startindex; i < endindex; i++) {
#ifdef DEBUG
			t = clock();
#endif
			//ws = m_TWPDL[i].path + L"\\" + m_TWPDL[i].name;
			//std::wstring ws (s.begin (), s.end ());
			//Gdiplus::Image image (ws.c_str ());
			//image.GetBounds (&boundsRect, &unit);

			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;
			std::string path_str = converter.to_bytes((m_TWPDL[i].path + m_TWPDL[i].name));
			img.GetImageSizeEx(path_str.c_str(), &Height, &Width);
			//m_TWPDL[i].width = boundsRect.Width;
			m_TWPDL[i].width = Width;
			//m_TWPDL[i].heigth = boundsRect.Height;
			m_TWPDL[i].heigth = Height;
			m_TWPDL[i].meret = -1;

#ifdef DEBUG
			std::cout << "Elem:" << "  " << m_TWPDL[i].path.c_str() << m_TWPDL[i].name.c_str() << " - " << m_TWPDL[i].width << " - " << m_TWPDL[i].heigth << std::endl;
			szamlalo++;
			elapsed = clock() - t;
			std::cout << "curently: " << szamlalo << " - " << elapsed << " " << "ms" << std::endl;
#endif
		}
		//Gdiplus::GdiplusShutdown (gdiplusToken);
	}
}