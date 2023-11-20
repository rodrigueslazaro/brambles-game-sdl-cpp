#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:state(is_active)
	, position(Vector2::Zero)
	, scale(1.0f)
	, rotation(0.0f)
	, game(game)
{
	game->addActor(this);
}

Actor::~Actor() {
	game->removeActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!components.empty())
		delete components.back();
}

void Actor::update(float delta_time) {
	if (state == is_active) {
		updateComponents(delta_time);
		updateActor(delta_time);
	}
}

void Actor::updateComponents(float delta_time) {
	for (auto comp : components)
		comp->update(delta_time);
}

void Actor::updateActor(float delta_time) {}

void Actor::addComponent(Component* component) {
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int my_order = component->getUpdateOrder();
	auto iter = components.begin();
	for (; iter != components.end(); ++iter)
		if (my_order < (*iter)->getUpdateOrder())
			break;

	// Inserts element before position of iterator
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component) {
	auto iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
		components.erase(iter);
}
