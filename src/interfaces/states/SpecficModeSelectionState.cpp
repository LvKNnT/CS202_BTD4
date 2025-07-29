#include "SpecificModeSelectionState.h"
#include "../managers/StateManager.h"
#include "../../core/Game.h"

SpecificModeSelectionState::SpecificModeSelectionState(): State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> backButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    panel->addPanelElement(backButton);

    title = std::make_shared<TextField>("Easy Mode", Game::Instance().getFontManager().getFont("Big"), WHITE, 60, width, (Vector2) {tablePos.x, tablePos.y + 70});
    panel->addPanelElement(title);

    modeInfoText = std::make_shared<TextField>("", Game::Instance().getFontManager().getFont("Medium"), WHITE, 30, 905, (Vector2) {tablePos.x + 70, tablePos.y + 75 + 60});
    panel->addPanelElement(modeInfoText);

    float sz = 150;
    float paddingBtn = 100;

    // 1022 - 4 * 150 = 422 - 100 = 322 / 4 = 80

    std::shared_ptr<PanelElement> standardButton = std::make_shared<StandardModeButton>(Game::Instance().getTextureManager().getTexture("Standard"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn, tablePos.y + 400});
    alternateBloonsButton = std::make_shared<AlternateBloonsModeButton>(Game::Instance().getTextureManager().getTexture("AlternateBloons"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + sz + 80, tablePos.y + 400});
    reverseButton = std::make_shared<ReverseModeButton>(Game::Instance().getTextureManager().getTexture("Reverse"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + 2 * sz + 2 * 80, tablePos.y + 400 });
    apopalyseButton = std::make_shared<ApopalyseModeButton>(Game::Instance().getTextureManager().getTexture("Apopalyse"), 1, sz, sz, (Vector2) {tablePos.x + paddingBtn + 3 * sz + 3 * 80, tablePos.y + 400});
    panel->addPanelElement(standardButton);
    panel->addPanelElement(alternateBloonsButton);
    panel->addPanelElement(reverseButton);
    panel->addPanelElement(apopalyseButton);

    Font font = Game::Instance().getFontManager().getFont("Medium");
    std::shared_ptr<PanelElement> toStandardModeText = std::make_shared<TextField>("Standard", font, WHITE, 30, sz, (Vector2) {tablePos.x + paddingBtn, tablePos.y + 400 + sz - 20});
    float textWidth = MeasureTextEx(font, "Alternative Bloons", 30, 0).x;
    std::shared_ptr<PanelElement> toAlternateBloonsModeText = std::make_shared<TextField>("Alternate Bloons", font, WHITE, 30, 0, (Vector2) {tablePos.x + paddingBtn + sz + 80 + (sz - textWidth) / 2 + 10, tablePos.y + 400 + sz - 20});
    std::shared_ptr<PanelElement> toReverseModeText = std::make_shared<TextField>("Reverse", font, WHITE, 30, sz, (Vector2) {tablePos.x + paddingBtn + 2 * sz + 2 * 80, tablePos.y + 400 + sz - 20});
    std::shared_ptr<PanelElement> toApopalyseModeText = std::make_shared<TextField>("Apopalyse", font, WHITE, 30, sz, (Vector2) {tablePos.x + paddingBtn + 3 * sz + 3 * 80, tablePos.y + 400 + sz - 20});
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
    auto stateManager = std::static_pointer_cast<StateManager>(Game::Instance().getStateManager());
    switch(event) {
        case Event::Type::HoveringStandardMode:
            stateManager->setMode(diffStr + "Standard");    
            break;
        case Event::Type::HoveringAlternateBloonsMode:
            modeInfo = "Bloons come from the opposite side of the tracks, and the order of Bloon waves in each round are reversed";
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(modeInfo);
            stateManager->setMode(diffStr + "Alternate Bloons");
            break;
        case Event::Type::HoveringReverseMode: 
            modeInfo = "Bloons have an altered RBE, making it more tricky";
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(modeInfo);
            stateManager->setMode(diffStr + "Reverse");
            break;
        case Event::Type::HoveringApopalyseMode:
            modeInfo = "Bloon waves progress without stopping";
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(modeInfo);
            stateManager->setMode(diffStr +  "Apopalyse");
            break;
        case Event::Type::ToEasyModeSelection:
            diff = Difficulty::Easy;
            setInfo();
            diffStr = "Easy - ";
            break;
        case Event::Type::ToMediumModeSelection:
            diff = Difficulty::Medium;
            diffStr = "Medium - ";
            setInfo();
            break;
        case Event::Type::ToHardModeSelection:
            diff = Difficulty::Hard;
            diffStr = "Hard - ";
            setInfo();
            break;
        case Event::Type::ToImpoppableModeSelection:
            diff = Difficulty::Impoppable;
            diffStr = "Impoppable - ";
            setInfo();
            break;
        default: 
            break;
    }

    stateManager->setModeInfo(getDifficultyInfo(diff));
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
            return "Start with 200 lives, $650 starting cash, win Rounds 1-40, all towers and upgrades cost 15% less than normal, all bloons move the slowest, at about -9% Medium speed, and the Round 40 MOAB has 66% HP.";
        case Difficulty::Medium:
            return "Start with 150 lives, $650 starting cash, win Rounds 1-60, all towers and upgrades cost their normal prices, and all bloons move at standard speed (+10% faster than on Easy).";
        case Difficulty::Hard:
            return "Start with 100 lives, $650 starting cash, win Rounds 3-80, all towers and upgrades cost +8% more, and all bloons move about +13% faster than on Medium (+25% faster than on Easy).";
        case Difficulty::Impoppable:
            return "Start with 1 life only, $650 starting cash, win Rounds 6-100, all towers and upgrades cost +20% more, and all bloons move about +13% faster than on Medium (+25% faster than on Easy).";
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

    std::dynamic_pointer_cast<TextField>(title)->setText(titleText);
    std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(getDifficultyInfo(diff));
}
