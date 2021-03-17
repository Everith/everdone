#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <iostream>

#include "..\\Log\Log.h"

#pragma comment(lib, "Ws2_32.lib") //Lib file alkalmazása

namespace Everith {
    class Web
    {
    public:
        Web ();
        ~Web ();
        // bool init (CURL*& conn, char* url);
        std::string getWebBody (std::string webname);
        std::string getBody (std::string webname);
        //std::string curlBody (std::string webname);
        //int writer (char* data, size_t size, size_t nmemb, std::string* writerData);

    private:
        void stripper (std::string webname);
        Log l;
        std::string m_url;
        std::string m_additive;
    };
}