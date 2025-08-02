#include "GameOverState.h"
#include "../../core/Game.h"

GameOverState::GameOverState() : State(377, 511, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "GAME OVER";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);

    std::shared_ptr<PanelElement> title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, 0, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    float buttonSpacing = (width - 97 * 2) / 3;
    std::shared_ptr<PanelElement> replayButton = std::make_shared<ReplayButton>(Game::Instance().getTextureManager().getTexture("Replay"), 0, 96, 97, (Vector2) {tablePos.x + buttonSpacing, tablePos.y + 70 + 60 + 50});
    std::shared_ptr<PanelElement> homeButton = std::make_shared<BackHome>(Game::Instance().getTextureManager().getTexture("Home"), 0, 96, 97, (Vector2) {tablePos.x + 2 * buttonSpacing + 96, tablePos.y + 70 + 60 + 50});
    panel->addPanelElement((title));
    panel->addPanelElement(replayButton);
    panel->addPanelElement(homeButton);
}

void GameOverState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 1.0, WHITE);
    if(panel) panel->draw();
}

void GameOverState::update(Event::Type event) {
}
