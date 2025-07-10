#include "EasyModeSelectionState.h"
#include "../../core/Game.h"

EasyModeSelectionState::EasyModeSelectionState(): State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> backButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    panel->addPanelElement(backButton);

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "Easy Mode";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);
    std::shared_ptr<PanelElement> title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, titleSize.x, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement(title);

    std::string modeInfo = "Start with 200 lives, $650 starting cash, win Rounds 1-40, all towers and upgrades\ncost 15% less than normal, all bloons move the slowest, at about -9% Medium\nspeed, and the Round 40 MOAB has 66% HP. Deflation sets the required\nrounds to 31-60";
    std::shared_ptr<PanelElement> modeInfoText = std::make_shared<TextField>(modeInfo.c_str(), Game::Instance().getFontManager().getFont("Medium"), WHITE, 30, 0, (Vector2) {tablePos.x + 70, tablePos.y + 75 + 60});
    panel->addPanelElement(modeInfoText);

    float sz = 150;
    float paddingBtn = 170;
    std::shared_ptr<PanelElement> toEasyStandardModeButton = std::make_shared<ToEasyStandardMode>(Game::Instance().getTextureManager().getTexture("Standard"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn, tablePos.y + 400});
    std::shared_ptr<PanelElement> toEasyPrimaryOnlyModeButton = std::make_shared<ToEasyStandardMode>(Game::Instance().getTextureManager().getTexture("PrimaryOnly"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + sz + 100, tablePos.y + 400 - 110});
    std::shared_ptr<PanelElement> toEasyDeflationdModeButton = std::make_shared<ToEasyStandardMode>(Game::Instance().getTextureManager().getTexture("Deflation"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + 2 * sz + 2 * 100, tablePos.y + 400 - 110});
    std::shared_ptr<PanelElement> toEasySandboxModeButton = std::make_shared<ToEasyStandardMode>(Game::Instance().getTextureManager().getTexture("Sandbox"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + sz + 100, tablePos.y + 400 + 110});
    panel->addPanelElement(toEasyStandardModeButton);
    panel->addPanelElement(toEasyPrimaryOnlyModeButton);
    panel->addPanelElement(toEasyDeflationdModeButton);
    panel->addPanelElement(toEasySandboxModeButton);

    Font font = Game::Instance().getFontManager().getFont("Medium");
    float textWidth = MeasureTextEx(font, "Standard", 30, 0).x;
    std::shared_ptr<PanelElement> toEasyStandardModeText = std::make_shared<TextField>("Standard", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + (sz - textWidth) / 2, tablePos.y + 400 + sz - 20});
    textWidth = MeasureTextEx(font, "Primary Only", 30, 0).x;
    std::shared_ptr<PanelElement> toEasyPrimaryOnlyModeText = std::make_shared<TextField>("Primary Only", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + sz + 100 + (sz - textWidth) / 2, tablePos.y + 400 - 110 + sz - 20});
    textWidth = MeasureTextEx(font, "Deflation", 30, 0).x;
    std::shared_ptr<PanelElement> toEasyDeflationdModeText = std::make_shared<TextField>("Deflation", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + 2 * sz + 2 * 100 + (sz - textWidth) / 2, tablePos.y + 400 - 110 + sz - 20});
    textWidth = MeasureTextEx(font, "Sandbox", 30, 0).x;
    std::shared_ptr<PanelElement> toEasySandboxModeText = std::make_shared<TextField>("Sandbox", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + sz + 100 + (sz - textWidth) / 2, tablePos.y + 400 + 110 + sz - 20});
    panel->addPanelElement(toEasyStandardModeText);
    panel->addPanelElement(toEasyPrimaryOnlyModeText);
    panel->addPanelElement(toEasyDeflationdModeText);
    panel->addPanelElement(toEasySandboxModeText);
}

void EasyModeSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();

}

void EasyModeSelectionState::update(Event::Type event) {
}
