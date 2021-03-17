//#pragma once
#include "../Core.h"

#define _ATL_APARTMENT_THREADED
#include <sapi.h>
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override something,
//but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//#include <string>

namespace speak {
    bool speak (const wchar_t *text);
}
