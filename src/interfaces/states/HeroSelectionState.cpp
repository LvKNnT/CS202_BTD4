#include "HeroSelectionState.h"
#include "../managers/StateManager.h"
#include "../../core/Game.h"

HeroSelectionState::HeroSelectionState() 
    : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> backButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    panel->addPanelElement(backButton);

    std::shared_ptr<PanelElement> title = std::make_shared<TextField>("Choose Your Hero", Game::Instance().getFontManager().getFont("Big"), WHITE, 60, width, (Vector2) {tablePos.x, tablePos.y + 70});
    panel->addPanelElement(title);

    heroInfoText = std::make_shared<TextField>("Heroes will buff a specific field of your towers.", Game::Instance().getFontManager().getFont("Medium"), WHITE, 30, 905, (Vector2) {tablePos.x + 70, tablePos.y + 75 + 60});
    panel->addPanelElement(heroInfoText);

    float szx = 150, szy = 300;
    float paddingBtn = 100;

    // 1022 - 4 * 150 = 422 - 100 = 322 / 4 = 80

    quincyButton = std::make_shared<QuincyButton>(Game::Instance().getTextureManager().getTexture("Quincy"), 1, szy, szx, (Vector2) {tablePos.x + paddingBtn, tablePos.y + 250});
    benjaminButton = std::make_shared<BenjaminButton>(Game::Instance().getTextureManager().getTexture("Benjamin"), 1, szy, szx, (Vector2) {tablePos.x + paddingBtn + szx + 80, tablePos.y + 250});
    rosaliaButton = std::make_shared<RosaliaButton>(Game::Instance().getTextureManager().getTexture("Rosalia"), 1, szy, szx, (Vector2) {tablePos.x + paddingBtn + 2 * szx + 2 * 80, tablePos.y + 250 });
    etienneButton = std::make_shared<EtienneButton>(Game::Instance().getTextureManager().getTexture("Etienne"), 1, szy, szx, (Vector2) {tablePos.x + paddingBtn + 3 * szx + 3 * 80, tablePos.y + 250});
    panel->addPanelElement(quincyButton);
    panel->addPanelElement(benjaminButton);
    panel->addPanelElement(rosaliaButton);
    panel->addPanelElement(etienneButton);

    Font font = Game::Instance().getFontManager().getFont("Medium");
    std::shared_ptr<PanelElement> QuincyText = std::make_shared<TextField>("Quincy", font, WHITE, 30, szx, (Vector2) {tablePos.x + paddingBtn, tablePos.y + 200 + szy - 20});
    std::shared_ptr<PanelElement> BenjaminText = std::make_shared<TextField>("Benjamin", font, WHITE, 30, szx, (Vector2) {tablePos.x + paddingBtn + 1 * szx + 1 * 80, tablePos.y + 200 + szy - 20});
    std::shared_ptr<PanelElement> RosaliaText = std::make_shared<TextField>("Rosalia", font, WHITE, 30, szx, (Vector2) {tablePos.x + paddingBtn + 2 * szx + 2 * 80, tablePos.y + 200 + szy - 20});
    std::shared_ptr<PanelElement> EtienneText = std::make_shared<TextField>("Etienne", font, WHITE, 30, szx, (Vector2) {tablePos.x + paddingBtn + 3 * szx + 3 * 80, tablePos.y + 200 + szy - 20});
    panel->addPanelElement(QuincyText);
    panel->addPanelElement(BenjaminText);
    panel->addPanelElement(RosaliaText);
    panel->addPanelElement(EtienneText);

}
void HeroSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void HeroSelectionState::update(Event::Type event) {
    switch(event) {
        case Event::Type::HoveringQuincy:
            std::dynamic_pointer_cast<TextField>(heroInfoText)->setText(HeroInfo::Instance().getHeroInfo(HeroType::Quincy)["description"]);
            break;
        case Event::Type::HoveringBenjamin:
            std::dynamic_pointer_cast<TextField>(heroInfoText)->setText(HeroInfo::Instance().getHeroInfo(HeroType::Benjamin)["description"]);
            break;
        case Event::Type::HoveringRosalia:
            std::dynamic_pointer_cast<TextField>(heroInfoText)->setText(HeroInfo::Instance().getHeroInfo(HeroType::Rosalia)["description"]);
            break;
        case Event::Type::HoveringEtienne:
            std::dynamic_pointer_cast<TextField>(heroInfoText)->setText(HeroInfo::Instance().getHeroInfo(HeroType::Etienne)["description"]);
            break;
    }
}

void HeroSelectionState::handleInput() {
    State::handleInput();
    if(std::dynamic_pointer_cast<Button>(quincyButton)->getState() == Button::State::None 
    && std::dynamic_pointer_cast<Button>(benjaminButton)->getState() == Button::State::None
    && std::dynamic_pointer_cast<Button>(rosaliaButton)->getState() == Button::State::None
    && std::dynamic_pointer_cast<Button>(etienneButton)->getState() == Button::State::None) {
        std::dynamic_pointer_cast<TextField>(heroInfoText)->setText("Heroes will buff a specific field of your towers.");   
    } 
}
