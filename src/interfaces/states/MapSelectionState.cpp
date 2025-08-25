#include "MapSelectionState.h"
#include "../../core/Game.h"

MapSelectionState::MapSelectionState() : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::shared_ptr<PanelElement> cancelMapSelectionButton = std::make_shared<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    nextMapButton = std::make_shared<NextMap>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 99, 88, (Vector2) {tablePos.x + width - 65 - 88, tablePos.y + (height - 99) / 2});
    previousMapButton = std::make_shared<PreviousMap>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 99, 84, (Vector2) {tablePos.x + 75, tablePos.y + (height - 99) / 2});
    ChooseMapButton[0] = std::make_shared<ChooseMonkeyLane>(Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb"), 0, 432, 600, (Vector2) {tablePos.x + (width - 600) / 2, tablePos.y + (height - 432) / 2});
    ChooseMapButton[1] = std::make_shared<ChooseJungle>(Game::Instance().getTextureManager().getTexture("JungleThumb"), 0, 432, 600, (Vector2) {tablePos.x + (width - 600) / 2, tablePos.y + (height - 432) / 2});
    ChooseMapButton[2] = std::make_shared<ChooseRinkRevenge>(Game::Instance().getTextureManager().getTexture("RinkRevengeThumb"), 0, 432, 600, (Vector2) {tablePos.x + (width - 600) / 2, tablePos.y + (height - 432) / 2});
    ChooseMapButton[3] = std::make_shared<ChooseDuneSea>(Game::Instance().getTextureManager().getTexture("DuneSeaThumb"), 0, 432, 600, (Vector2) {tablePos.x + (width - 600) / 2, tablePos.y + (height - 432) / 2});
    ChooseMapButton[4] = std::make_shared<ChooseAttackOnBloon>(Game::Instance().getTextureManager().getTexture("AttackOnBloonThumb"), 0, 432, 600, (Vector2) {tablePos.x + (width - 600) / 2, tablePos.y + (height - 432) / 2});
    ChooseMapButton[5] = std::make_shared<CommingSoon>(Game::Instance().getTextureManager().getTexture("CommingSoon2"), 0, 390, 392, (Vector2) {tablePos.x + (width - 392) / 2, tablePos.y + (height - 390) / 2});
    
    mapName[0] = std::make_shared<TextField>("Monkey Lane", Game::Instance().getFontManager().getFont("Medium-Big"), YELLOW, 45, 1022, (Vector2) {tablePos.x, tablePos.y + (height - 432) / 2 + 432 + 5});
    mapName[1] = std::make_shared<TextField>("Jungle", Game::Instance().getFontManager().getFont("Medium-Big"), YELLOW, 45, 1022, (Vector2) {tablePos.x, tablePos.y + (height - 432) / 2 + 432 + 5});
    mapName[2] = std::make_shared<TextField>("Rink Revenge", Game::Instance().getFontManager().getFont("Medium-Big"), YELLOW, 45, 1022, (Vector2) {tablePos.x, tablePos.y + (height - 432) / 2 + 432 + 5});
    mapName[3] = std::make_shared<TextField>("Dune Sea", Game::Instance().getFontManager().getFont("Medium-Big"), YELLOW, 45, 1022, (Vector2) {tablePos.x, tablePos.y + (height - 432) / 2 + 432 + 5});
    mapName[4] = std::make_shared<TextField>("Attack On Bloon", Game::Instance().getFontManager().getFont("Medium-Big"), YELLOW, 45, 1022, (Vector2) {tablePos.x, tablePos.y + (height - 432) / 2 + 432 + 5});
    mapName[5] = std::make_shared<TextField>("", Game::Instance().getFontManager().getFont("Medium-Big"), YELLOW, 45, 1022, (Vector2) {tablePos.x, tablePos.y + (height - 432) / 2 + 432 + 5});
    panel->addPanelElement((cancelMapSelectionButton));
    panel->addPanelElement((nextMapButton));
    panel->addPanelElement((previousMapButton));
    for(int i = 0; i < maxMap; i++) {
        panel->addPanelElement((ChooseMapButton[i]));
        panel->addPanelElement(mapName[i]);
        if(i > 0) {
            ChooseMapButton[i]->setAvailable(false);
            mapName[i]->setAvailable(false);
        }
    }

    std::shared_ptr<PanelElement> title = std::make_shared<TextField>("CHOOSE A MAP", Game::Instance().getFontManager().getFont("Big"), WHITE, 60, width, (Vector2) {tablePos.x, tablePos.y + 100});
    panel->addPanelElement((title));

    curMap = 0;
    previousMapButton->setAvailable(false);

    saveGameTexture = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("SaveGame"), 56, 50, (Vector2) {tablePos.x + (width - 600) / 2 + 600 - 25, tablePos.y + (height - 432) / 2 - 25});
    panel->addPanelElement(saveGameTexture);

    infoButton = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 50, 50, (Vector2) {tablePos.x + (width - 600) / 2, tablePos.y + (height - 432) / 2});
    panel->addPanelElement(infoButton);

    infoTextbox = std::make_shared<MovableTextbox>("", Game::Instance().getFontManager().getFont("Small"), WHITE, 20, 300);
    panel->addPanelElement(infoTextbox);
    infoTextbox->setAvailable(false);
}

void MapSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void MapSelectionState::handleInput() {
    State::handleInput();
    saveGameTexture->setAvailable(std::dynamic_pointer_cast<StateManager>(Game::Instance().getStateManager())->canLoadGame(static_cast<MapType>(curMap * 2)));
    infoButton->setAvailable(curMap < maxMap - 1);
    if(std::dynamic_pointer_cast<Button>(infoButton)->getState() == Button::State::None) {
        infoTextbox->setAvailable(false);
    }
}

void MapSelectionState::update(Event::Type event) {
    switch(event) {
        case Event::Type::MoveNext:
            ChooseMapButton[curMap]->setAvailable(false);
            mapName[curMap]->setAvailable(false);
            ChooseMapButton[++curMap]->setAvailable(true);
            mapName[curMap]->setAvailable(true);
            break;
        case Event::Type::MovePrevious:
            ChooseMapButton[curMap]->setAvailable(false);
            mapName[curMap]->setAvailable(false);
            ChooseMapButton[--curMap]->setAvailable(true);
            mapName[curMap]->setAvailable(true);
            break;
        case Event::Type::HoveringInfo:
            infoTextbox->setAvailable(true);
            std::dynamic_pointer_cast<TextField>(infoTextbox)->setText(MapInfo::Instance().getMapInfo(static_cast<MapType>(curMap * 2))["description"]);
            break;
        default:
            if(Event::Type::ToMonkeyLane <= event && event <= Event::Type::ToAttackOnBloon) {
                infoTextbox->setAvailable(false);
            }
    }
    previousMapButton->setAvailable(curMap > 0);
    nextMapButton->setAvailable(curMap + 1 < maxMap);
    saveGameTexture->setAvailable(std::dynamic_pointer_cast<StateManager>(Game::Instance().getStateManager())->canLoadGame(static_cast<MapType>(curMap * 2)));
}