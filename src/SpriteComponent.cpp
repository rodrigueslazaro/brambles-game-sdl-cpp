#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int draw_order)
    :Component(owner),
    texture(nullptr),
    draw_order(draw_order),
    texture_width(0),
    texture_height(0)
{
    owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() {
	owner->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_Rect r;
        r.w = static_cast<int>(texture_width * owner->getScale());
        r.h = static_cast<int>(texture_width * owner->getScale());
        r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
        r.y = static_cast<int>(owner->getPosition().y - r.h / 2);
        SDL_RenderCopyEx(
            renderer,
            texture,
            nullptr,
            &r,
            -Math::ToDegrees(owner->getRotation()),
            nullptr,
            SDL_FLIP_NONE
        );
    }
}

void SpriteComponent::setTexture(SDL_Texture* texture) {
    this->texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);
}