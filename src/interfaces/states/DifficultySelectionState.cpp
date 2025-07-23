#include "DifficultySelectionState.h"
#include "../../core/Game.h"

DifficultySelectionState::DifficultySelectionState() : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> backButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    panel->addPanelElement(backButton);

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "CHOOSE A DIFFICULTY";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);
    std::shared_ptr<PanelElement> title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, 0, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement(title);

    // 1022 - 99-> 923 - 3 * 233 -> 324 / 4 = 24
    float buttonPadding = 24;
    float sz = 200;
    std::shared_ptr<PanelElement> easyButton = std::make_shared<ToEasyModeSelection>(Game::Instance().getTextureManager().getTexture("Easy"), 1, sz, sz, (Vector2) {tablePos.x + 49 + buttonPadding, tablePos.y + (height - sz) / 2});
    std::shared_ptr<PanelElement> mediumButton = std::make_shared<ToMediumModeSelection>(Game::Instance().getTextureManager().getTexture("Medium"), 1, sz, sz, (Vector2) {tablePos.x + 49 + 2 * buttonPadding + sz, tablePos.y + (height - sz) / 2});
    std::shared_ptr<PanelElement> hardButton = std::make_shared<ToHardModeSelection>(Game::Instance().getTextureManager().getTexture("Hard"), 1, sz, sz, (Vector2) {tablePos.x + 49 + 3 * buttonPadding + 2 * sz, tablePos.y + (height - sz) / 2});
    std::shared_ptr<PanelElement> impoppableButton = std::make_shared<ToImpoppableModeSelection>(Game::Instance().getTextureManager().getTexture("Impoppable"), 1, sz, sz, (Vector2) {tablePos.x + 49 + 4 * buttonPadding + 3 * sz, tablePos.y + (height - sz) / 2});
    panel->addPanelElement(easyButton);
    panel->addPanelElement(mediumButton);
    panel->addPanelElement(hardButton);
    panel->addPanelElement(impoppableButton);
    
    Font textFont = Game::Instance().getFontManager().getFont("Medium-Big");
    float textWidth = MeasureTextEx(textFont, "Easy", (float) 45, 1.0).x;
    std::shared_ptr<PanelElement> easyText = std::make_shared<TextField>("Easy", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 49 + buttonPadding + (sz - textWidth) / 2, tablePos.y + (height - sz) / 2 + sz + 15});
    textWidth = MeasureTextEx(textFont, "Medium", (float) 45, 1.0).x;
    std::shared_ptr<PanelElement> mediumText = std::make_shared<TextField>("Medium", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 49 + 2 * buttonPadding + sz + (sz - textWidth) / 2, tablePos.y + (height - sz) / 2 + sz + 15});
    textWidth = MeasureTextEx(textFont, "Hard", (float) 45, 1.0).x;
    std::shared_ptr<PanelElement> hardText = std::make_shared<TextField>("Hard", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 49 + 3 * buttonPadding + 2 * sz + (sz - textWidth) / 2, tablePos.y + (height - sz) / 2 + sz + 15});
    textWidth = MeasureTextEx(textFont, "Impoppable", (float) 45, 1.0).x;
    std::shared_ptr<PanelElement> impoppableText = std::make_shared<TextField>("Impoppable", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 49 + 4 * buttonPadding + 3 * sz + (sz - textWidth) / 2, tablePos.y + (height - sz) / 2 + sz + 15});
    panel->addPanelElement(easyText);
    panel->addPanelElement(mediumText);
    panel->addPanelElement(hardText);
    panel->addPanelElement(impoppableText);
}

void DifficultySelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void DifficultySelectionState::update(Event::Type event) {
}
