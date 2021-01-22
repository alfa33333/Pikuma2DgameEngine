#include <iostream>
#include "./Game/Game.h"


int main(int argc, char* arv[]) {
    Game game;

    game.Initialize();
    game.Run();
    game.Destroy();
   
    return 0;
}
