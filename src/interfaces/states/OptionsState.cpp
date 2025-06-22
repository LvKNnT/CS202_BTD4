#include "OptionsState.h"
#include "../../core/Game.h"

OptionsState::OptionsState() : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "Options";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);
    std::unique_ptr<PanelElement> title = std::make_unique<TextField>(titleText, titleFont, WHITE, titleSize.y, titleSize.x, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement(std::move(title));

    std::unique_ptr<PanelElement> cancelOptionsStateButton = std::make_unique<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    std::unique_ptr<PanelElement> higherSoundButton = std::make_unique<HigherSound>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 50, 44, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 44, tablePos.y + 70 + titleFontSize + 30});
    std::unique_ptr<PanelElement> lowerSoundButton = std::make_unique<LowerSound>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 50, 42, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 2 * 44, tablePos.y + 70 + titleFontSize + 30});
    std::unique_ptr<PanelElement> higherMusicButton = std::make_unique<HigherMusic>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 50, 44, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 44, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    std::unique_ptr<PanelElement> lowerMusicButton = std::make_unique<LowerMusic>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 50, 42, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 2 * 44, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    std::unique_ptr<PanelElement> autoNextRoundButton = std::make_unique<AutoNextRound>(Game::Instance().getTextureManager().getTexture("Tick"), 0, 54, 52, (Vector2) {tablePos.x + width - 70 - 52, tablePos.y + 70 + titleFontSize + 30 + 54 * 2 + 50 * 2});
    std::unique_ptr<PanelElement> unAutoNextRoundButton = std::make_unique<UnAutoNextRound>(Game::Instance().getTextureManager().getTexture("Untick"), 0, 54, 52, (Vector2) {tablePos.x + width - 70 - 52, tablePos.y + 70 + titleFontSize + 30 + 54 * 2 + 50 * 2});
    unAutoNextRoundButton->setAvailable(false);
    panel->addPanelElement(std::move(cancelOptionsStateButton));
    panel->addPanelElement(std::move(autoNextRoundButton));
    panel->addPanelElement(std::move(higherSoundButton));
    panel->addPanelElement(std::move(lowerSoundButton));
    panel->addPanelElement(std::move(higherMusicButton));
    panel->addPanelElement(std::move(lowerMusicButton));
    panel->addPanelElement(std::move(unAutoNextRoundButton));
    
    Font textFont = Game::Instance().getFontManager().getFont("Medium-Big");
    std::unique_ptr<PanelElement> soundText = std::make_unique<TextField>("Sounds", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 80, tablePos.y + 70 + titleFontSize + 30});
    std::unique_ptr<PanelElement> musicText = std::make_unique<TextField>("Music", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 80, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    std::unique_ptr<PanelElement> autoNextRoundText = std::make_unique<TextField>("Auto Next Round", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 80, tablePos.y + 70 + titleFontSize + 30 + 54 * 2 + 50 * 2});
    panel->addPanelElement(std::move(soundText));
    panel->addPanelElement(std::move(musicText));
    panel->addPanelElement(std::move(autoNextRoundText));

    std::unique_ptr<PanelElement> soundTexture = std::make_unique<TextureField>(Game::Instance().getTextureManager().getTexture("Volume5"), 54, 431, (Vector2) {tablePos.x + width - 70 - 431, tablePos.y + 70 + titleFontSize + 30});
    std::unique_ptr<PanelElement> musicTexture = std::make_unique<TextureField>(Game::Instance().getTextureManager().getTexture("Volume5"), 54, 431, (Vector2) {tablePos.x + width - 70 - 431, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    panel->addPanelElement(std::move(soundTexture));
    panel->addPanelElement(std::move(musicTexture));
}

void OptionsState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void OptionsState::update(Event::Type event) {

}