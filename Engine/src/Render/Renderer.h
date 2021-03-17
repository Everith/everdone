#pragma once
#include "..\Core.h"
#include "Everith/Window/Windows/EveWindow.h"

class Renderer{
private:
    EveWindow* m_WindowID;
public:
    virtual ~Renderer () {};

    virtual EveWindow* setWindowID() =0;
    };
