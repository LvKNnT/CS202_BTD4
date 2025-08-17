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
    auto stateManager = std::static_pointer_cast<StateManager>(Game::Instance().getStateManager());
    auto diff = Game::Instance().getGameLogic().getDifficulty();
    std::string diffInfo = "";
    switch(event) {
        case Event::Type::HoveringStandardMode:
            break;
        case Event::Type::HoveringAlternateBloonsMode:
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(ModeInfo::Instance().getModeInfo(ModeType::Alternative)["description"]);
            break;
        case Event::Type::HoveringReverseMode: 
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(ModeInfo::Instance().getModeInfo(ModeType::Reverse)["description"]);
            break;
        case Event::Type::HoveringApopalyseMode:
            std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(ModeInfo::Instance().getModeInfo(ModeType::Apopalypse)["description"]);
            break;
        default: 
            break;
        }
}

void SpecificModeSelectionState::handleInput() {
    State::handleInput();
    setInfo();
    auto diff = Game::Instance().getGameLogic().getDifficulty();

    if(std::dynamic_pointer_cast<Button>(alternateBloonsButton)->getState() == Button::State::None 
    && std::dynamic_pointer_cast<Button>(reverseButton)->getState() == Button::State::None
    && std::dynamic_pointer_cast<Button>(apopalyseButton)->getState() == Button::State::None) {
        std::dynamic_pointer_cast<TextField>(modeInfoText)->setText(DifficultyInfo::Instance().getDifficultyInfo(diff)["description"]);   
    } 
}


void SpecificModeSelectionState::setInfo() {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    auto diff = Game::Instance().getGameLogic().getDifficulty();
    std::string titleText = DifficultyInfo::Instance().getDifficultyInfo(diff)["name"] + " Mode";
    std::dynamic_pointer_cast<TextField>(title)->setText(titleText);
}
