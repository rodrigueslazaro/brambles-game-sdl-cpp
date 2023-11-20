#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class Game {
public:
    Game();

    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);
   	const std::vector<class Actor*>& GetActors() const { return actors; }

	enum GameState {
		is_playing,
		is_paused,
		is_quit
	};
	
	GameState GetState() const { return game_state; }
	void SetState(GameState state) { game_state = state; }

    void addSprite(class SpriteComponent* sprite);
    void removeSprite(class SpriteComponent* sprite);

    SDL_Texture* getTexture(const std::string& file_name);
private:
    void processInput();
    void updateGame();
    void generateOutput();
    void loadData();
    void unloadData();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running;
    bool is_updating_actors;
    Uint32 ticks_count;
    GameState game_state;

    std::unordered_map<std::string, SDL_Texture*> textures;
    std::vector<class SpriteComponent*> sprites;
    std::vector<Actor*> actors;
    std::vector<Actor*> pending_actors;

    class Player* player;
};