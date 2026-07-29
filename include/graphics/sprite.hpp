#pragma once

#include <raylib.h>

class Sprite {
public:
    Sprite(const Texture2D& texture, const double& rotation = 0.0, const double& scale = 1.0);
    Sprite();

    const Texture2D& getTexture() const;

    void setRotation(const double& newRotation);
    const double& getRotation() const;

    const double& getScale() const;
private:
    Texture2D _texture;
    double _rotation;
    double _scale;
};