#include "Component.h"
#include "Actor.h"
#include "LevelLoader.h"

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

void Component::LoadProperties(const rapidjson::Value& inObj)
{
	JsonHelper::GetInt(inObj, "updateOrder", update_order);
}

void Component::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	JsonHelper::AddInt(alloc, inObj, "updateOrder", update_order);
}
