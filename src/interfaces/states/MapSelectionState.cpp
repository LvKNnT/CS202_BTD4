#include "MapSelectionState.h"
#include "../../core/Game.h"

MapSelectionState::MapSelectionState() : State(516, 705, Game::Instance().getTextureManager().getTexture("MapSelectionBackground")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::unique_ptr<PanelElement> cancelMapSelectionButton = std::make_unique<Button>(Button::Type::CancelMapSelection, Game::Instance().getTextureManager().getTexture("XButton"), 0, 39, 38, (Vector2) {tablePos.x + width - 40 - 38, tablePos.y + 45});
    std::unique_ptr<PanelElement> nextMapButton = std::make_unique<Button>(Button::Type::NextMap, Game::Instance().getTextureManager().getTexture("NextButton"), 0, 46, 40, (Vector2) {tablePos.x + width - 40 - 40, tablePos.y + height / 2 - 46});
    std::unique_ptr<PanelElement> previousMapButton = std::make_unique<Button>(Button::Type::PreviousMap, Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 46, 38, (Vector2) {tablePos.x + 50, tablePos.y + height / 2 - 46});
    
    panel->addPanelElement(std::move(cancelMapSelectionButton));
    panel->addPanelElement(std::move(nextMapButton));
    panel->addPanelElement(std::move(previousMapButton));
}

void MapSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 3.0, WHITE);
    if(panel) panel->draw();
}
