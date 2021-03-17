#pragma once
#include "..\config.h"
#include <sstream>

#ifdef DEBUG
#include "..\Log\Log.h"
#endif // DEBUG

namespace Everith {
    class WPScan
    {
    public:
        WPScan (std::wstring path);
        ~WPScan ();
        std::vector<Wallpaper_data> getWPDL () { return m_WPDL; }
        void Scan ();
        void RiperScan (std::vector<Wallpaper_data>& WPDL, bool& isdone);

    private:
        bool initScan ();
        void GetSizeRiper (std::vector<Wallpaper_data>& WPDL);
        void LoadSaveFile ();
        bool isExist (std::wstring search);
        void Save ();
        void MegreLists ();
        void ScanFiles (std::vector<std::wstring>& s, std::wstring path);
        void ScanMappa (std::wstringstream& ss, std::wstring& word, std::vector<std::wstring>& s, std::wstring& path);
        void ScanImage (std::wstringstream& ss, std::wstring& word, std::wstring& path);
        void GetSize ();
        void GetSizeThread (int startindex, int endindex);
    private:
        std::wstringstream  m_FS;
        std::wstring m_path;
        std::vector<Wallpaper_data> m_WPDL;
        std::vector<Wallpaper_data> m_TWPDL;
#ifdef DEBUG
        Log l;
#endif // DEBUG
    };
}