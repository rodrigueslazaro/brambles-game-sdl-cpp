#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int update_order)
	:owner(owner)
	,update_order(update_order)
{
	// Add to actor's vector of components
	owner->addComponent(this);
}

Component::~Component()
{
	owner->removeComponent(this);
}

void Component::update(float delta_time) { }
