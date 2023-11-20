#pragma once
#include <vector>
#include "Math.h"

class Actor {
public:
	enum TypeID {
		TActor = 0,
		NUM_ACTOR_TYPES
	};

	static const char* TypeNames[NUM_ACTOR_TYPES];

    enum State {
        is_active,
        is_paused,
        is_dead
    };
    Actor(class Game* game);
    virtual ~Actor();

    void update(float delta_time);
    void updateComponents(float delta_time);
    virtual void updateActor(float delta_time);

    void setPosition(const Vector2& pos) { position = pos; }
    const Vector2& getPosition() const { return position; }
    State getState() {return state;}
    void setScale(float s) { scale = s; }
    float getScale() {return scale;}
    float getRotation() {return rotation;}
    class Game* getGame() {return game;}

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    Vector2 GetForward() const { return Vector2(Math::Cos(rotation), -Math::Sin(rotation)); }

   	virtual void LoadProperties(const rapidjson::Value& inObj);
	virtual void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const;

 	template <typename T>
	static Actor* Create(class Game* game, const rapidjson::Value& inObj)
	{
		// Dynamically allocate actor of type T
		T* t = new T(game);
		// Call LoadProperties on new actor
		t->LoadProperties(inObj);
		return t;
	}
    // Search through component vector for one of type
	Component* GetComponentOfType(Component::TypeID type)
	{
		Component* comp = nullptr;
		for (Component* c : components)
		{
			if (c->GetType() == type)
			{
				comp = c;
				break;
			}
		}
		return comp;
	}

	virtual TypeID GetType() const { return TActor; }
   	const std::vector<Component*>& GetComponents() const { return components; }
	void SetState(State state) { this->state = state; }

private:
    State state;

    Vector2 position;
    float scale;
    float rotation;

    std::vector<class Component*> components;
    class Game* game;
};