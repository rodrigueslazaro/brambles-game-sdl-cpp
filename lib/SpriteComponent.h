#pragma once
#include <SDL2/SDL.h>
#include "Component.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int draw_order = 100);
    ~SpriteComponent();
    
    virtual void draw(SDL_Renderer* renderer);
    virtual void setTexture(SDL_Texture* texture);

    int getDrawOrder() const {return draw_order;}
    int getTextureHeight() const {return texture_height;}
    int getTextureWidth() const {return texture_width;}
private:
    SDL_Texture* texture;
    int draw_order;
    int texture_width;
    int texture_height;
};