#include "GameOverState.h"
#include "../../core/Game.h"

GameOverState::GameOverState() : State(377, 511, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> titleText = std::make_shared<BackHome>(Game::Instance().getTextureManager().getTexture("GameOver"), 0, 179, 400, (Vector2) {tablePos.x + 55, tablePos.y - 50});
    float buttonSpacing = (width - 97 * 2) / 3;
    std::shared_ptr<PanelElement> replayButton = std::make_shared<ReplayButton>(Game::Instance().getTextureManager().getTexture("Replay"), 0, 96, 97, (Vector2) {tablePos.x + buttonSpacing, tablePos.y + 70 + 60 + 50});
    std::shared_ptr<PanelElement> homeButton = std::make_shared<BackHome>(Game::Instance().getTextureManager().getTexture("Home"), 0, 96, 97, (Vector2) {tablePos.x + 2 * buttonSpacing + 96, tablePos.y + 70 + 60 + 50});
    panel->addPanelElement(titleText);
    panel->addPanelElement(replayButton);
    panel->addPanelElement(homeButton);
}

void GameOverState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 1.0, WHITE);
    if(panel) panel->draw();
}

void GameOverState::update(Event::Type event) {
}
