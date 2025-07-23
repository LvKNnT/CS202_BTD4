#include "SpecificModeSelectionState.h"
#include "../../core/Game.h"

SpecificModeSelectionState::SpecificModeSelectionState(): State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> backButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    panel->addPanelElement(backButton);

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "Easy Mode";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);
    title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, 0, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement(title);

    modeInfoText = std::make_shared<TextField>("", Game::Instance().getFontManager().getFont("Medium"), WHITE, 30, 930, (Vector2) {tablePos.x + 70, tablePos.y + 75 + 60});
    panel->addPanelElement(modeInfoText);

    float sz = 150;
    float paddingBtn = 100;

    // 1022 - 4 * 150 = 422 - 100 = 322 / 4 = 80

    std::shared_ptr<PanelElement> standardButton = std::make_shared<StandardMode>(Game::Instance().getTextureManager().getTexture("Standard"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn, tablePos.y + 400});
    alternateBloonsButton = std::make_shared<AlternateBloonsMode>(Game::Instance().getTextureManager().getTexture("AlternateBloons"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + sz + 80, tablePos.y + 400});
    reverseButton = std::make_shared<ReverseMode>(Game::Instance().getTextureManager().getTexture("Reverse"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + 2 * sz + 2 * 80, tablePos.y + 400 });
    apopalyseButton = std::make_shared<ApopalyseMode>(Game::Instance().getTextureManager().getTexture("Apopalyse"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + 3 * sz + 3 * 80, tablePos.y + 400});
    panel->addPanelElement(standardButton);
    panel->addPanelElement(alternateBloonsButton);
    panel->addPanelElement(reverseButton);
    panel->addPanelElement(apopalyseButton);

    Font font = Game::Instance().getFontManager().getFont("Medium");
    float textWidth = MeasureTextEx(font, "Standard", 30, 0).x;
    std::shared_ptr<PanelElement> toStandardModeText = std::make_shared<TextField>("Standard", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + (sz - textWidth) / 2, tablePos.y + 400 + sz - 20});
    textWidth = MeasureTextEx(font, "Alternative Bloons", 30, 0).x;
    std::shared_ptr<PanelElement> toAlternateBloonsModeText = std::make_shared<TextField>("Alternate Bloons", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + sz + 80 + (sz - textWidth) / 2, tablePos.y + 400 + sz - 20});
    textWidth = MeasureTextEx(font, "Reverse", 30, 0).x;
    std::shared_ptr<PanelElement> toReverseModeText = std::make_shared<TextField>("Reverse", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + 2 * sz + 2 * 80 + (sz - textWidth) / 2, tablePos.y + 400 + sz - 20});
    textWidth = MeasureTextEx(font, "Apopalyse", 30, 0).x;
    std::shared_ptr<PanelElement> toApopalyseModeText = std::make_shared<TextField>("Apopalyse", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + 3 * sz + 3 * 80 + (sz - textWidth) / 2, tablePos.y + 400 + sz - 20});
    panel->addPanelElement(toStandardModeText);
    panel->addPanelElement(toAlternateBloonsModeText);
    panel->addPanelElement(toReverseModeText);
    panel->addPanelElement(toApopalyseModeText);
}

void SpecificModeSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();

}

void SpecificModeSelectionState::update(Event::Type event) {
    std::string modeInfo;
    switch(event) {
        case Event::Type::HoveringAlternateBloonsMode:
            modeInfo = "Bloons come from the opposite side of the tracks, and the order of Bloon waves in each round are reversed";
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(modeInfo);
            break;
        case Event::Type::HoveringReverseMode: 
            modeInfo = "Bloons have an altered RBE, making it more tricky";
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(modeInfo);
            break;
        case Event::Type::HoveringApopalyseMode:
            modeInfo = "Bloon waves progress without stopping";
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(modeInfo);
            break;
        case Event::Type::ToEasyModeSelection:
            diff = Difficulty::Easy;
            setInfo();
            break;
        case Event::Type::ToMediumModeSelection:
            diff = Difficulty::Medium;
            setInfo();
            break;
        case Event::Type::ToHardModeSelection:
            diff = Difficulty::Hard;
            setInfo();
            break;
        case Event::Type::ToImpoppableModeSelection:
            diff = Difficulty::Impoppable;
            setInfo();
            break;
        default: 
            break;
    }
}

void SpecificModeSelectionState::handleInput() {
    State::handleInput();

    if(std::dynamic_pointer_cast<Button>(alternateBloonsButton)->getState() == Button::State::None 
    && std::dynamic_pointer_cast<Button>(reverseButton)->getState() == Button::State::None
    && std::dynamic_pointer_cast<Button>(apopalyseButton)->getState() == Button::State::None) {
        std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(getDifficultyInfo(diff));   
    } 
}

std::string SpecificModeSelectionState::getDifficultyInfo(Difficulty type) const {
    switch(type) {
        case Difficulty::Easy:
            return "Start with 200 lives, $650 starting cash, win Rounds 1-40, all towers and upgrades cost 15% less than normal, all bloons move the slowest, at about -9% Medium speed, and the Round 40 MOAB has 66% HP. Deflation sets the required rounds to 31-60";
        case Difficulty::Medium:
            return "Start with 150 lives, $650 starting cash, win Rounds 1-60, all towers and upgrades cost their normal prices, and all bloons move at standard speed (+10% faster than on Easy)";
        case Difficulty::Hard:
            return "Start with 100 lives, $650 starting cash, win Rounds 3-80, all towers and upgrades cost +8% more, and all bloons move about +13% faster than on Medium (+25% faster than on Easy)";
        case Difficulty::Impoppable:
            return "Start with 1 life only, $650 starting cash, win Rounds 6-100, all towers and upgrades cost +20% more, and all bloons move about +13% faster than on Medium (+25% faster than on Easy)";
    }
    return "";
}

void SpecificModeSelectionState::setInfo()
{
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    std::string titleText = "";
    std::string diffInfo = getDifficultyInfo(diff);
    switch(diff) {
        case Difficulty::Easy:
            titleText = "Easy Mode";
            break;
        case Difficulty::Medium:
            titleText = "Medium Mode";
            break;
        case Difficulty::Hard:
            titleText = "Hard Mode";
            break;
        case Difficulty::Impoppable:
            titleText = "Impoppable Mode";
            break;
    }

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);
    std::dynamic_pointer_cast<TextField>(title)->setTextAndPos(titleText, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(getDifficultyInfo(diff));
}
