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
    // always wait until 16ms have passed from the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count+ 16));

    float delta_time = (SDL_GetTicks() - ticks_count) / 1000.0f;

    if (delta_time > 0.05f)
        delta_time = 0.05f;
    
    ticks_count = SDL_GetTicks();

    is_updating_actors = true;
    for (auto actor : actors)
        actor->update(delta_time);
    is_updating_actors = false;

    for (auto pending : pending_actors)
        actors.emplace_back(pending);
    pending_actors.clear();

    std::vector<Actor*> dead_actors;
    for (auto actor : actors)
        if (actor->getState() == Actor::is_dead)
            dead_actors.emplace_back(actor);

    for (auto actor : dead_actors)
        delete actor;

    


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

void Game::addActor(Actor* actor) {
    if(is_updating_actors)
        pending_actors.emplace_back(actor);
    else
        actors.emplace_back(actor);
}

void Game::removeActor(Actor* actor) {
	auto iter = std::find(pending_actors.begin(), pending_actors.end(), actor);
	if (iter != pending_actors.end()) {
		std::iter_swap(iter, pending_actors.end() - 1);
		pending_actors.pop_back();
	}

	iter = std::find(actors.begin(), actors.end(), actor);
	if (iter != actors.end()) {
		std::iter_swap(iter, actors.end() - 1);
		actors.pop_back();
	}
}
