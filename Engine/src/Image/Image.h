#pragma once
namespace Everith {
#define _CRT_SECURE_NO_WARNINGS

    class Image
    {
    public:
        Image ();
        ~Image ();
        bool GetImageSizeEx (const char *fn, int *x, int *y);
    private:
    };
}