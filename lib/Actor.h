#pragma once
#include <vector>
#include "Math.h"

class Actor {
public:
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
private:
    State state;

    Vector2 position;
    float scale;
    float rotation;

    std::vector<class Component*> components;
    class Game* game;
};