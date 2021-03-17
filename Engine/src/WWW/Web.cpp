#include "Web.h"

#include <iostream>

#include <fstream>
#include <iostream>


//#include "curl/curl.h"


namespace Everith {
    Web::Web ()
    {
    }

    Web::~Web ()
    {
    }

    std::string Web::getWebBody (std::string webname)
    {
        l.Pass ("Internet DATA:");
        std::string source;
        stripper (webname);

        WSADATA wsaData;
        if (WSAStartup (MAKEWORD (2, 2), &wsaData) != 0) {
            std::cout << "WSAStartup failed.\n";
            system ("pause");
        }

        SOCKET Socket = socket (AF_INET, SOCK_STREAM, 0);
        struct hostent* host;
        host = gethostbyname (m_url.c_str ());

        SOCKADDR_IN SockAddr;
        SockAddr.sin_port = htons (80);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

        connect (Socket, (SOCKADDR*)(&SockAddr), sizeof (SockAddr));

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string sendRequest = "GET ";
        sendRequest += webname;
        //sendRequest += m_additive;
        sendRequest += " HTTP/1.1\r\n";
        sendRequest += "Host: ";
        sendRequest += m_url;
        sendRequest += "\r\n";
        sendRequest += "Connection: close\r\n";
        sendRequest += "Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n";
        sendRequest += "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; fr; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n";
        sendRequest += "\r\n";
        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        size_t requestSize = sendRequest.size () + 1;
        char cRequest[5000];
        int i = 0;
        strncpy_s (cRequest, sendRequest.c_str (), requestSize);
        l.Error (cRequest);
        send (Socket, cRequest, strlen (cRequest), 0);

        //put data in string
        char buffer[10000];
        int nDataLength;
        while ((nDataLength = recv (Socket, buffer, 10000, 0)) > 0) {
            int i = 0;
            while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
                source += buffer[i];
                i += 1;
            }
        }
        closesocket (Socket);
        WSACleanup ();

        l.Report (source);
        return source;
    }
    std::string Web::getBody (std::string webname)
    {
        stripper (webname);
        std::string source = "";
        WSADATA WSAData;
        WSAStartup (MAKEWORD (2, 2), &WSAData);
        SOCKET Socket;
        SOCKADDR_IN sin;
        struct hostent* host;
        host = gethostbyname (m_url.c_str ());

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string sendRequest = "GET ";
        //sendRequest += m_additive;
        sendRequest += webname;
        sendRequest += " HTTP/1.1\r\n";
        sendRequest += "Host: ";
        sendRequest += m_url;
        sendRequest += "\r\n";
        //sendRequest += "Connection: keep - alive\r\n";
        sendRequest += "Connection: close\r\n";
        sendRequest += "Cache-Control : max-age = 604800\r\n";
        //sendRequest += "User-Agent : Mozilla / 5.0 (Macintosh; Intel Mac OS X 10_6_8) AppleWebKit / 535.1 (KHTML, like Gecko) Chrome / 14.0.835.186 Safari / 535.1\r\n";
        //sendRequest += "Accept: text/html, application/xhtml+xml, application/xml; q=0.9, / ; q=0.8\r\n";
        //sendRequest += "Accept-Encoding: gzip, deflate, sdch\r\n";
        //sendRequest += "Accept-Language : en - US, en; q = 0.8\r\n";
        //sendRequest += "Accept-Charset: ISO - 8859 - 1, utf - 8; q = 0.7, *; q = 0.3\r\n";
        //sendRequest += "Cookie: NID = 51 = XHrnCh - WA2BjwFpfjavZ1dxy6JT98N0ojBEtkxBnP9uUEr3cLvm2ETGlr0q0JhWWcgth - z7Dm7J0NU - UpA77SiDtF2rh1DhzRRToW1jA0Ia7HmOzFepL9TdIW9MDacAK; rememberme = true; PREF = ID = 5a917ae1d013ee33:U = 8c5a025c53669947 : FF = 0 : TM = 1317242244 : LM = 1317291115 : GM = 1 : S = n1cOehpkL6SuVhsK\r\n";
        sendRequest += "\r\n";
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        size_t requestSize = sendRequest.size () + 1;
        char cRequest[5000];
        int i = 0;
        strncpy_s (cRequest, sendRequest.c_str (), requestSize); //string copy to char array

        Socket = socket (AF_INET, SOCK_STREAM, 0);
        sin.sin_addr.s_addr = *((unsigned long*)host->h_addr);
        sin.sin_family = AF_INET;
        sin.sin_port = htons (80); // port HTTP.

        connect (Socket, (SOCKADDR*)& sin, sizeof (sin));

        l.Error (cRequest);
        send (Socket, cRequest, strlen (cRequest), 0); // HTML request

        //put data in string
        char buffer[100000];
        int nDataLength;
        while ((nDataLength = recv (Socket, buffer, 100000, 0)) > 0) {
            int i = 0;
            while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
                source += buffer[i];
                i += 1;
            }
        }

        closesocket (Socket);
        WSACleanup ();

        l.Pass (source);
        std::ofstream output;
        output.open ("Data\\TesztFictionLive.txt");
        //std::cout << fb << std::endl;
        output << source << "\n";

        output.close ();

        return source;
    }

    //static int writer (char* data, size_t size, size_t nmemb, std::string* writerData){
    //    if (writerData == NULL)
    //        return 0;

    //    writerData->append (data, size * nmemb);

    //    return size * nmemb;
    //}
    //std::string curlBody (std::string webname){
    //    std::string source;

    //    curl_global_init (CURL_GLOBAL_ALL);
    //    CURL* curl = nullptr;
    //    curl = curl_easy_init ();
    //    if (curl)
    //    {
    //        curl_easy_setopt (curl, CURLOPT_URL, webname);
    //        curl_easy_setopt (curl, CURLOPT_WRITEDATA, &source);
    //        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writer);
    //        //CURLcode code = curl_easy_perform (curl);
    //        curl_easy_cleanup (curl);
    //    }
    //    curl_global_cleanup ();
    //    Log l;
    //    l.Pass (source);
    //    return source;
    //}

    void Web::stripper (std::string webname){
        std::string url;
        std::string addictive;

#ifdef DEBUG
        l.Report (webname);
#endif // DEBUG

        int i = 0;
        char buffer[8];
        for (int i = 0; i < 8; i++)
        {
            std::cout << webname[i] << std::endl;
            buffer[i] = webname[i];
        }
        char etalon[9] = "https://";
        char etalon0[9] = "http://";
        int score = 0;
        while (buffer[i] == etalon[i])
        {
            score++;
            i++;
        }
        if (score >= 8)
        {
            webname.erase (webname.begin (), webname.begin () + 8);
        }
        else
        {
            score = 0;
            i = 0;
            while (buffer[i] == etalon0[i])
            {
                score++;
                i++;
            }
            if (score >= 7)
            {
                webname.erase (webname.begin (), webname.begin () + 7);
            }
        }
#ifdef DEBUG
        l.Report (webname);
#endif // DEBUG

        i = 0;
        while (webname[i] != '/' && webname[i] != '\0')
        {
            m_url += webname[i];
            i++;
        }
        webname.erase (webname.begin (), webname.begin () + i);
#ifdef DEBUG
        l.Report (webname);
        l.Pass (m_url);
#endif // DEBUG

        i = 0;
        while (webname[i] != '\0')
        {
            m_additive += webname[i];
            i++;
        }
        if (i < 1)
        {
            m_additive += '/';
        }
#ifdef DEBUG
        l.Pass (m_url);
        l.Pass (m_additive);
#endif // DEBUG
    }
}