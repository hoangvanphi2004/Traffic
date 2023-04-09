#include "../Include/Game.h"
#include "../Include/def.h"

int main(int argc, char *args[]){
    Game* game = new Game("GoHome", SCREEN_WIDTH, SCREEN_HEIGHT);
    //game.menuScreen();
    game->runningScreen();
    return 0;
}
