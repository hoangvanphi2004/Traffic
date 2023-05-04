#include "../Include/Game.h"
#include "../Include/def.h"

int main(int argc, char *args[]){
    Game* game = new Game("Traffic", SCREEN_WIDTH, SCREEN_HEIGHT);

    game->menuScreen();

    return 0;
}
