#include "GameObject.h"

// Tbh, idk whether isActiveFlag should be true or false by default.
GameObject::GameObject() : position({0.0f, 0.0f}), size({0.0f, 0.0f}), rotation(0.0f), tag(""), isActiveFlag(true) {}
GameObject::GameObject(Vector2 position, Vector2 size, float rotation, const std::string& tag)
    : position(position), size(size), rotation(rotation), tag(tag), isActiveFlag(true) {}
GameObject::~GameObject() = default;