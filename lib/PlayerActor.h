#pragma once
#include "Actor.h"
#include <cstdint>

class PlayerActor : public Actor {
public:
	PlayerActor(class Game* game);

	void updateActor(float delta_time) override;
	void processKeyboard(const uint8_t* state);

	float getRightSpeed() const { return right_speed; }
	float getDownSpeed() const { return down_speed; }
private:
	float right_speed;
	float down_speed;
};
