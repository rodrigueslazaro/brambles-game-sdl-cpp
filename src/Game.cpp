#include "Game.h"

Game::Game() {
    is_running = true;
    ticks_count = 0;
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log ("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow(
        "Gamedev in C++!",
        100,
        100,
        1280,
        720,
        0
    );
    if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }   
    renderer = SDL_CreateRenderer(
        window,
        -1,
        0
    );
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::shutdown() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::updateGame() {
    float delta_time = (SDL_GetTicks() - ticks_count) / 1000.0f;
    ticks_count = SDL_GetTicks();
    

}

void Game::generateOutput() {
    SDL_SetRenderDrawColor (
        renderer,
        150,
        100,
        100,
        255
    );
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

}

void Game::runLoop() {
    while (is_running) {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        is_running = false;
    }
}