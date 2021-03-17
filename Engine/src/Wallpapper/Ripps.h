#pragma once
#include <vector>
#include "..\Log\Log.h"
#include "Struct/WallpaperData.h"
namespace Everith {
    class Rips
    {
    public:
        Rips ();
        ~Rips ();

        void RipsSort ();
        void isWallpaper ();
        bool Events (int event);
        void EventAction (std::wstring Desk, std::wstring Mobil, std::wstring good);

        void rate_wallpappers ();
        bool WallpaperEvent (Wallpaper_data image);

    private:
        void LoadRiper ();
    private:
        bool m_WP = false;
        bool m_isdone = false;
        Log l;
        std::vector<Wallpaper_data> m_WPDL;
        Wallpaper_data m_WPD;
        int index = 0;
    };
}