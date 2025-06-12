#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() = default;
GameObjectManager::~GameObjectManager() = default;

void GameObjectManager::addGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjectList.push_back(std::move(gameObject));
}

void GameObjectManager::removeGameObject(GameObject* gameObject) {
    // This method should not be called, as we manage game objects using smart pointers
}

void GameObjectManager::drawGameObjects() const {
    for (const auto& gameObject : gameObjectList) {
        if (gameObject->isActive()) {
            gameObject->draw();
        }
    }
}