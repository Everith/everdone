#pragma once

#include"platform/platform.h"


namespace Everith {
class Game {
public:
    Game(platform* platform): p(platform) {p->platform_startup();};
    void loop();

private:
    bool isrunning = 1;
    platform* p;
 
};
}