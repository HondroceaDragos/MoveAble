#include "../../include/graphics/sprite.hpp"

Sprite::Sprite(const Texture2D& texture, const double& rotation, const double& scale):
    _texture(texture), _rotation(rotation), _scale(scale) {}
Sprite::Sprite() {}

const Texture2D &Sprite::getTexture() const { return _texture; }

void Sprite::setRotation(const double& newRotation) { _rotation = newRotation; }
const double &Sprite::getRotation() const { return _rotation; }

const double &Sprite::getScale() const { return _scale; }
