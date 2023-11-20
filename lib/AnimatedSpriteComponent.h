#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimatedSpriteComponent : public SpriteComponent {
public:
    AnimatedSpriteComponent(class Actor* owner, int draw_order = 100);

    void update(float delta_time) override;
    void setAnimationTextures(const std::vector<SDL_Texture*>& textures);

    float getAnimationFPS() {return animationFPS;}
    void setAnimationFPS(float fps) {animationFPS = fps;}
private:
    std::vector<SDL_Texture*> animation_textures;
    float current_frame;
    float animationFPS;
};