#include "OptionsState.h"
#include "../../core/Game.h"
#include "../managers/AudioManager.h"

OptionsState::OptionsState() : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "Options";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);
    std::shared_ptr<PanelElement> title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, 0, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement((title));

    std::shared_ptr<PanelElement> cancelOptionsStateButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    std::shared_ptr<PanelElement> higherSoundButton = std::make_shared<HigherSound>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 50, 44, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 44, tablePos.y + 70 + titleFontSize + 30});
    std::shared_ptr<PanelElement> lowerSoundButton = std::make_shared<LowerSound>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 50, 42, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 2 * 44, tablePos.y + 70 + titleFontSize + 30});
    std::shared_ptr<PanelElement> higherMusicButton = std::make_shared<HigherMusic>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 50, 44, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 44, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    std::shared_ptr<PanelElement> lowerMusicButton = std::make_shared<LowerMusic>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 50, 42, (Vector2) {tablePos.x + width - 70 - 431 - 10 - 2 * 44, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    std::shared_ptr<PanelElement> autoNextRoundButton = std::make_shared<AutoNextRound>(Game::Instance().getTextureManager().getTexture("Tick"), 0, 54, 52, (Vector2) {tablePos.x + width - 70 - 52, tablePos.y + 70 + titleFontSize + 30 + 54 * 2 + 50 * 2});
    panel->addPanelElement((cancelOptionsStateButton));
    panel->addPanelElement((autoNextRoundButton));
    panel->addPanelElement((higherSoundButton));
    panel->addPanelElement((lowerSoundButton));
    panel->addPanelElement((higherMusicButton));
    panel->addPanelElement((lowerMusicButton));
    
    Font textFont = Game::Instance().getFontManager().getFont("Medium-Big");
    std::shared_ptr<PanelElement> soundText = std::make_shared<TextField>("Sounds", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 80, tablePos.y + 70 + titleFontSize + 30});
    std::shared_ptr<PanelElement> musicText = std::make_shared<TextField>("Music", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 80, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
    std::shared_ptr<PanelElement> autoNextRoundText = std::make_shared<TextField>("Auto Next Round", textFont, WHITE, 45, 0, (Vector2) {tablePos.x + 80, tablePos.y + 70 + titleFontSize + 30 + 54 * 2 + 50 * 2});
    panel->addPanelElement((soundText));
    panel->addPanelElement((musicText));
    panel->addPanelElement((autoNextRoundText));

    for(int i = 0; i < 6; i++) {
        soundTexture[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("Volume" + std::to_string(i * 20)), 54, 431, (Vector2) {tablePos.x + width - 70 - 431, tablePos.y + 70 + titleFontSize + 30});
        soundTexture[i]->setAvailable(false);
        musicTexture[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("Volume" + std::to_string(i * 20)), 54, 431, (Vector2) {tablePos.x + width - 70 - 431, tablePos.y + 70 + titleFontSize + 30 + 54 + 50});
        musicTexture[i]->setAvailable(false);

        panel->addPanelElement((soundTexture[i]));
        panel->addPanelElement((musicTexture[i]));
    }
}

void OptionsState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void OptionsState::update(Event::Type event) {
    auto soundManagerPtr = std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager());
    switch(event) {
        case Event::Type::HigherMusic:
            case Event::Type::LowerMusic:
                resetMusicTextures();
                musicTexture[soundManagerPtr->getVolume(AudioType::MusicSound) / 20]->setAvailable(true);
                break;
        case Event::Type::HigherSound:
            case Event::Type::LowerSound:
                resetSoundTextures();
                soundTexture[soundManagerPtr->getVolume(AudioType::SFXSound) / 20]->setAvailable(true);
                break;
        case Event::Type::AutoNextRound:
            Game::Instance().getGameLogic().activeAutoPlay();
            break;
        case Event::Type::UnAutoNextRound:
            Game::Instance().getGameLogic().unactiveAutoPlay();
            break;
        case Event::Type::None:
            resetMusicTextures();
            resetSoundTextures();
            musicTexture[soundManagerPtr->getVolume(AudioType::MusicSound) / 20]->setAvailable(true);
            soundTexture[soundManagerPtr->getVolume(AudioType::SFXSound) / 20]->setAvailable(true);
            break;
    }
}

void OptionsState::resetMusicTextures() {
    for(int i = 0; i < 6; i++) {
        musicTexture[i]->setAvailable(false);
    }
}

void OptionsState::resetSoundTextures() {
    for(int i = 0; i < 6; i++) {
        soundTexture[i]->setAvailable(false);
    }
}
