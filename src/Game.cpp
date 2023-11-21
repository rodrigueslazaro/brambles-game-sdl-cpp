#include "Game.h"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "PlayerActor.h"
#include "BGSpriteComponent.h"
#include "LevelLoader.h"

Game::Game()
:window(nullptr)
,renderer(nullptr)
,is_running(true)
,is_updating_actors(false)
{}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log ("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG == 0)) {
        SDL_Log ("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow(
        "Gamedev in C++!",
        100,
        100,
        1024,
        768,
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

    loadData();

    ticks_count = SDL_GetTicks();

    return true;
}


void Game::unloadData() {
	while (!actors.empty())
		delete actors.back();
	for (auto i : textures)
		SDL_DestroyTexture(i.second);
	textures.clear();
}

void Game::shutdown() {
    unloadData();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
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
    SDL_SetRenderDrawColor ( renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto sprite : sprites)
        sprite->draw(renderer);

    SDL_RenderPresent(renderer);
}

void Game::loadData() {
   	// Load English text
	loadText("txt/english.gptext");
	// Create HUD
	// mHUD = new HUD(this);

	// Load the level from file
	// LevelLoader::LoadLevel(this, "ast/level1.gplevel");
	
	// Start music
	// mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// Enable relative mouse mode for camera look
	// SDL_SetRelativeMouseMode(SDL_TRUE);
	// // Make an initial call to get relative to clear out
	// SDL_GetRelativeMouseState(nullptr, nullptr);




	player = new PlayerActor(this);
	player->setPosition(Vector2(100.0f, 384.0f));
	player->setScale(1.5f);

	// // Create actor for the background (this doesn't need a subclass)
	// Actor* temp = new Actor(this);
	// temp->setPosition(Vector2(512.0f, 384.0f));
	// // Create the "far back" background
	// BGSpriteComponent* bg = new BGSpriteComponent(temp);
	// bg->setScreenSize(Vector2(1024.0f, 768.0f));
	// std::vector<SDL_Texture*> bgtexs = {
	// 	getTexture("img/sky.png"),
	// 	getTexture("img/forest.png")
	// };
	// bg->setBGTextures(bgtexs);
	// bg->setScrollSpeed(-100.0f);
	// // Create the closer background
	// bg = new BGSpriteComponent(temp, 50);
	// bg->setScreenSize(Vector2(1024.0f, 768.0f));
	// bgtexs = {
	// 	getTexture("img/field.png"),
	// 	getTexture("img/field.png")
	// };
	// bg->setBGTextures(bgtexs);
	// bg->setScrollSpeed(-200.0f);
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
    player->processKeyboard(state);
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

SDL_Texture* Game::getTexture(const std::string& file_name) {
	SDL_Texture* texture = nullptr;
	// Is the texture already in the map?
	auto i = textures.find(file_name);
	if (i != textures.end()) {
		texture = i->second;
	} else {
		SDL_Surface* surface = IMG_Load(file_name.c_str());
		if (!surface) {
			SDL_Log("Failed to load texture file %s", file_name.c_str());
			return nullptr;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!texture) {
			SDL_Log("Failed to convert surface to texture for %s", file_name.c_str());
			return nullptr;
		}

		textures.emplace(file_name.c_str(), texture);
	}
	return texture;
}

// ask gepeto, maybe optimize
void Game::addSprite(SpriteComponent* sprite) {
    int draw_order = sprite->getDrawOrder();
    auto i = sprites.begin();
    for (; i != sprites.end(); ++i)
        if (draw_order < (*i)->getDrawOrder())
            break;
    sprites.insert(i, sprite);
}

void Game::removeSprite(SpriteComponent* sprite) {
	// (We can't swap because it ruins ordering)
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	sprites.erase(iter);
}

void Game::loadText(const std::string& file_name) {
	// Clear the existing map, if already loaded
	text.clear();

	rapidjson::Document doc;
	if (!LevelLoader::LoadJSON(file_name, doc)) {
		SDL_Log("Failed to load text file %s", file_name.c_str());
		return;
	}

	// Parse the text map
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin();
		itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			text.emplace(itr->name.GetString(),
				itr->value.GetString());
		}
	}
}

const std::string& Game::getText(const std::string& key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = text.find(key);
	if (iter != text.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}