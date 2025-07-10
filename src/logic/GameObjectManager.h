#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

// Using the design pattern Observer to draw all game objects

#include "raylib.h"
#include <vector>
#include <memory>
#include "GameObject.h"

class GameObjectManager {
public:
    GameObjectManager();
    ~GameObjectManager();

    // Method to add/remove game objects
    void addGameObject(std::unique_ptr<GameObject> gameObject);
    void removeGameObject(GameObject* gameObject); // should not be called

    // Method to draw all game objects
    void drawGameObjects() const;
private:
    std::vector<std::unique_ptr<GameObject>> gameObjectList; // Collection of all game objects
};

#endif // GAMEOBJECTMANAGER_H