#include "MainMenuState.h"
#include "../../core/Game.h"

MainMenuState::MainMenuState()
    : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("MainMenu")) {
    panel = std::make_unique<Panel>();
    
    Texture buttonTex = Game::Instance().getTextureManager().getTexture("MainMenuButton");
    int buttonWidth = buttonTex.width * 2;
    int buttonHeight = buttonTex.height * 2;
    Vector2 firstButtonPos = {static_cast<float>((Properties::screenWidth - buttonWidth) / 2), 300};
    int spacingY = 50;
    
    std::unique_ptr<PanelElement> newGameButton = std::make_unique<Button>(Button::Type::NewGame, buttonTex, 30, buttonHeight, buttonWidth, firstButtonPos);
    std::unique_ptr<PanelElement> resumeButton = std::make_unique<Button>(Button::Type::Resume, buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + buttonHeight});
    std::unique_ptr<PanelElement> optionsButton = std::make_unique<Button>(Button::Type::Options, buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + 2 * buttonHeight});
    std::unique_ptr<PanelElement> exitButton = std::make_unique<Button>(Button::Type::Exit, buttonTex, 30, buttonHeight, buttonWidth, Vector2{firstButtonPos.x, firstButtonPos.y + 3 * buttonHeight});
    
    panel->addPanelElement(std::move(newGameButton));
    panel->addPanelElement(std::move(resumeButton));
    panel->addPanelElement(std::move(optionsButton));
    panel->addPanelElement(std::move(exitButton));
}
