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

    void Update(float delta_time);
    void UpdateComponents(float delta_time);
    virtual void UpdateActor(float delta_time);

    void setState(State state);
    State getState();
    void setPosition(Vector2 position);
    Vector2 getPosition();


    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
private:
    State state;
    Vector2 position;
    float scale;
    float rotation;
    std::vector<class Component*> components;
    class Game* game;
};