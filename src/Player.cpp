#include "Player.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"

Player::Player(Game* game)
	:Actor(game)
	,right_speed(0.0f)
	,down_speed(0.0f)
{
	// Create an animated sprite component
	AnimatedSpriteComponent* asc = new AnimatedSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->getTexture("img/bina1.png"),
		game->getTexture("img/bina2.png"),
		game->getTexture("img/bina3.png"),
		game->getTexture("img/bina4.png"),
	};
	asc->setAnimationTextures(anims);
}

void Player::updateActor(float delta_time) {
	Actor::updateActor(delta_time);
	// Update position based on speeds and delta time
	Vector2 pos = getPosition();
	pos.x += right_speed * delta_time;
	pos.y += down_speed * delta_time;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
		pos.x = 25.0f;
	else if (pos.x > 500.0f)
		pos.x = 500.0f;
	if (pos.y < 25.0f)
		pos.y = 25.0f;
	else if (pos.y > 743.0f)
		pos.y = 743.0f;
	setPosition(pos);
}

void Player::processKeyboard(const uint8_t* state) {
	right_speed = 0.0f;
	down_speed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
		right_speed += 250.0f;
	if (state[SDL_SCANCODE_A])
		right_speed -= 250.0f;
	// up/down
	if (state[SDL_SCANCODE_S])
		down_speed += 300.0f;
	if (state[SDL_SCANCODE_W])
		down_speed -= 300.0f;
}
