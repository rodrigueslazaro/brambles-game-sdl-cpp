#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "Actor.h"

class Game {
public:
    Game();

    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(Actor* actor);
    void removeActor(Actor* actor);

private:
    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running;
    bool is_updating_actors;
    Uint32 ticks_count;

    std::vector<Actor*> actors;
    std::vector<Actor*> pending_actors;
};