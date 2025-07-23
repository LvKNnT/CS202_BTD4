#include "AreYouSureState.h"
#include "../../core/Game.h"

AreYouSureState::AreYouSureState() : State(377, 511, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "Are you sure?";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);

    std::shared_ptr<PanelElement> title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, 0, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement((title));

    std::shared_ptr<PanelElement> okButton = std::make_shared<BackHome>(Game::Instance().getTextureManager().getTexture("OkButton"), 0, 91, 85, (Vector2) {tablePos.x + 110, tablePos.y + height - 100 - 91});
    std::shared_ptr<PanelElement> cancelHomeButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 87, 84, (Vector2) {tablePos.x + width - 110 - 84, tablePos.y + height - 100 - 87});
    panel->addPanelElement(okButton);
    panel->addPanelElement(cancelHomeButton);
}

void AreYouSureState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 1.0, WHITE);
    if(panel) panel->draw();
}

void AreYouSureState::update(Event::Type Event) {

}