#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent {
public:
	BGSpriteComponent(class Actor* owner, int draw_order = 10);

	void update(float delta_time) override;
	void draw(SDL_Renderer* renderer) override;

	void setBGTextures(const std::vector<SDL_Texture*>& textures);
	void setScreenSize(const Vector2& size) { screen_size = size; }
	void setScrollSpeed(float speed) { scroll_speed = speed; }
	float getScrollSpeed() const { return scroll_speed; }
private:
	struct BGTexture {
		SDL_Texture* texture;
		Vector2 offset;
	};
	std::vector<BGTexture> BGtextures;
	Vector2 screen_size;
	float scroll_speed;
};
