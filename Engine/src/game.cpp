#include "game.h"


namespace Everith { 

void Game::loop(){
    while (isrunning){
        //TODO stuff
        p->platform_pump_messages();
    } 
}
}