#pragma once
#include "..\Core.h"

#include "../File/file.h"

namespace Everith {
    struct Wallpaper_data {
        std::wstring path;
        std::wstring name;
        int width;
        int heigth;
        //double ratio;
        int meret;
        //std::vector<std::string> tags;
    };

    class Wallpaper {
    private:
        //Variables:
        //Log l;

        //Functions:

    public:
        //Variables:
        //Functions:
        Wallpaper ();
        ~Wallpaper ();

        //Set()
        //Update()
        //Sort()
        void SortRips ();

        void setTags (std::wstring info);
        void Wallpaper_Set (std::vector<std::wstring> tags);

        void Wallpaper_data_load (std::vector <Wallpaper_data>* wall_data_reggel, std::vector<std::wstring> tags);
        void wallpaper_update ();
        void Wallpaper_data_update (std::wstring path);

        void sort_wallpaper ();
        void sort_files (std::vector<Wallpaper_data> lista);

        //bool WallpaperEvent (Wallpaper_data image);
        void rate_wallpappers ();
    };
}