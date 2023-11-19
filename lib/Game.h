#include <SDL2/SDL.h>

class Game {
public:
    Game();
    bool initialize();
    void runLoop();
    void shutdown();
private:
    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running;
    Uint32 ticks_count;
};