#pragma once
#include "Core.h"
#include "File/File.h"

namespace  Everith {
    class Config
    {
    private:
    public:
        Config ();
        ~Config ();

        void check ();
        std::string conf (std::string name);
    };
}