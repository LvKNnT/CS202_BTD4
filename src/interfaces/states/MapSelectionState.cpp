#include "MapSelectionState.h"
#include "../../core/Game.h"

MapSelectionState::MapSelectionState() : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> cancelMapSelectionButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    nextMapButton = std::make_shared<NextMap>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 99, 88, (Vector2) {tablePos.x + width - 65 - 88, tablePos.y + (height - 99) / 2});
    previousMapButton = std::make_shared<PreviousMap>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 99, 84, (Vector2) {tablePos.x + 75, tablePos.y + (height - 99) / 2});
    ChooseMapButton[0] = std::make_shared<ChooseMonkeyLane>(Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb"), 0, 360, 500, (Vector2) {tablePos.x + (width - 500) / 2, tablePos.y + (height - 360) / 2});
    ChooseMapButton[1] = std::make_shared<ChooseJungle>(Game::Instance().getTextureManager().getTexture("JungleThumb"), 0, 360, 500, (Vector2) {tablePos.x + (width - 500) / 2, tablePos.y + (height - 360) / 2});
    ChooseMapButton[2] = std::make_shared<CommingSoon>(Game::Instance().getTextureManager().getTexture("CommingSoon2"), 0, 390, 392, (Vector2) {tablePos.x + (width - 392) / 2, tablePos.y + (height - 390) / 2});
    
    panel->addPanelElement((cancelMapSelectionButton));
    panel->addPanelElement((nextMapButton));
    panel->addPanelElement((previousMapButton));
    for(int i = 0; i < maxMap; i++) {
        panel->addPanelElement((ChooseMapButton[i]));
        if(i > 0) ChooseMapButton[i]->setAvailable(false);
    }

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "CHOOSE A MAP";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);

    std::shared_ptr<PanelElement> title = std::make_shared<TextField>(titleText, titleFont, WHITE, titleSize.y, 0, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement((title));

    curMap = 0;
    previousMapButton->setAvailable(false);
}

void MapSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void MapSelectionState::update(Event::Type event) {
    switch(event) {
        case Event::Type::MoveNext:
            ChooseMapButton[curMap]->setAvailable(false);
            ChooseMapButton[++curMap]->setAvailable(true);
            break;
        case Event::Type::MovePrevious:
            ChooseMapButton[curMap]->setAvailable(false);
            ChooseMapButton[--curMap]->setAvailable(true);
            break;
    }
    previousMapButton->setAvailable(curMap > 0);
    nextMapButton->setAvailable(curMap + 1 < maxMap);
}