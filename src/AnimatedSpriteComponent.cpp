#include "AnimatedSpriteComponent.h"
#include "Math.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,current_frame(0.0f)
	,animationFPS(18.0f) 
{
}

void AnimatedSpriteComponent::setAnimationTextures(
    const std::vector<SDL_Texture*>& textures) {
    animation_textures = textures;
    if (animation_textures.size() > 0) {
        current_frame = 0;
        setTexture(animation_textures[0]);
    }
}

void AnimatedSpriteComponent::update(float delta_time) {
	SpriteComponent::update(delta_time);
	if (animation_textures.size() > 0) {
		current_frame += animationFPS * delta_time;
		while (current_frame >= animation_textures.size())
			current_frame -= animation_textures.size();
		setTexture(animation_textures[static_cast<int>(current_frame)]);
    }
}