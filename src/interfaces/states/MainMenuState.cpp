#include "MainMenuState.h"
#include "../../core/Game.h"

MainMenuState::MainMenuState()
    : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("MainMenu")) {
    panel = std::make_unique<Panel>();
    
    Texture buttonTex = Game::Instance().getTextureManager().getTexture("MainMenuButton");
    int buttonWidth = buttonTex.width;
    int buttonHeight = buttonTex.height;
    Vector2 firstButtonPos = {static_cast<float>((Properties::screenWidth - buttonWidth) / 2), 300};
    int spacingY = 50;
    
    std::shared_ptr<PanelElement> newGameButton = std::make_shared<NewGame>(buttonTex, 30, buttonHeight, buttonWidth, firstButtonPos);
    std::shared_ptr<PanelElement> continueButton = std::make_shared<Continue>(buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + buttonHeight});
    std::shared_ptr<PanelElement> resumeButton = std::make_shared<Resume>(buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + 2 * buttonHeight});
    std::shared_ptr<PanelElement> optionsButton = std::make_shared<Options>(buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + 3 * buttonHeight});
    std::shared_ptr<PanelElement> exitButton = std::make_shared<Exit>(buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + 4 * buttonHeight});
    
    panel->addPanelElement((newGameButton));
    panel->addPanelElement((continueButton));
    panel->addPanelElement((resumeButton));
    panel->addPanelElement((optionsButton));
    panel->addPanelElement((exitButton));
}
