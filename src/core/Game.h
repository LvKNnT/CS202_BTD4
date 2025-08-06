#ifndef GAME_H
#define GAME_H

#include <memory>

// UI/UX
#include "../interfaces/managers/StateManager.h"
#include "../interfaces/managers/TextureManager.h"
#include "../interfaces/managers/AnimationManager.h"
#include "../interfaces/managers/FontManager.h"
#include "../interfaces/managers/AudioManager.h"
#include "../interfaces/states/StateStack.h"
#include "../interfaces/states/MainMenuState.h"
#include "../interfaces/states/LoadingState.h"
#include "../interfaces/audio/MyAudio.h"

#include "IObserver.h"

// Logic
#include "../logic/GameLogic.h"

class Game {
public:
    static Game& Instance();

    Game();
    ~Game();

    void LoadContent();
    void UnloadContent();

    void initialize();
    void render();
    void update(float deltaTime);
    void requestExit();
    bool isExit() const;

    TextureManager &getTextureManager();
    AnimationManager &getAnimationManager();
    FontManager &getFontManager();
    std::shared_ptr<IObserver> getAudioManager();
    std::shared_ptr<IObserver> getStateManager();

    GameLogic &getGameLogic();
private:
    bool exit; // for exit 

    // Managers
    TextureManager textureManager;
    FontManager fontManager;
    AnimationManager animationManager;
    // pointer for observer pattern
    std::shared_ptr<IObserver> audioManager;
    std::shared_ptr<IObserver> stateManager;    

    GameLogic gameLogic;

    void loadTexture();
    void loadFont();
    void loadSound();
    void loadTowerTexture();
    void loadAnimationTexture();
};

#endif // GAME_H