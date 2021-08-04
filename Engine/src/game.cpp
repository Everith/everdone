#include "game.h"


namespace Everith { 

void Game::loop(){
    int result;
    while (isrunning){
        //TODO stuff
        isrunning = p->platform_pump_messages();
        
    } 
}
}