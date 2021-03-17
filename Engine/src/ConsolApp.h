#pragma once
#include <string>

namespace Everith {
    class ConsolApp
    {
    private:
    public:
        ConsolApp ();
        ~ConsolApp ();

        void Commands (std::string command);
    };
}