#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// base class for all game objects

#include "raylib.h"
#include <string>
#include "../interfaces/Drawable.h"
#include "../interfaces/Updatable.h"

class GameObject : public Drawable, public Hitbox {
public:
    GameObject();
    // Constructor with position, size, rotation, and tag
    GameObject(Vector2 position, Vector2 size, float rotation, const std::string& tag);
    virtual ~GameObject();

    // Check if the object is active
    virtual bool isActive() const = 0;
    virtual void setActive(bool active) = 0;

protected:
    Vector2 position; // Position of the game object
    Vector2 size; // Size of the game object
    float rotation; // Rotation angle for the game object
    std::string tag; // Tag for identifying the game object
    bool isActiveFlag; // Flag to indicate if the object is active
};

#endif // GAMEOBJECT_H