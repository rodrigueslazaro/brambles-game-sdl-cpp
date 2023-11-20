#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,scroll_speed(0.0f) { }

void BGSpriteComponent::update(float delta_time) {
	SpriteComponent::update(delta_time);
	for (auto& bg : BGtextures) {
		bg.offset.x += scroll_speed * delta_time;
		if (bg.offset.x < -screen_size.x)
			bg.offset.x = (BGtextures.size() - 1) * screen_size.x - 1;
	}
}

void BGSpriteComponent::draw(SDL_Renderer* renderer) {
	// Draw each background texture
	for (auto& bg : BGtextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(screen_size.x);
		r.h = static_cast<int>(screen_size.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(owner->getPosition().x - r.w / 2 + bg.offset.x);
		r.y = static_cast<int>(owner->getPosition().y - r.h / 2 + bg.offset.y);

		// Draw this background
		SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
	}
}

void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures) {
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.texture = tex;
		// Each texture is screen width in offset
		temp.offset.x = count * screen_size.x;
		temp.offset.y = 0;
		BGtextures.emplace_back(temp);
		count++;
	}
}
