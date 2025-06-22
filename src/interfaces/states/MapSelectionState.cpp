#include "MapSelectionState.h"
#include "../../core/Game.h"

MapSelectionState::MapSelectionState() : State(754, 1022, Game::Instance().getTextureManager().getTexture("Table")) {
    Vector2 tablePos = {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)};
    panel = std::make_unique<Panel>();

    std::unique_ptr<PanelElement> cancelMapSelectionButton = std::make_unique<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("XButton"), 0, 44, 42, (Vector2) {tablePos.x + width - 60 - 42, tablePos.y + 75});
    std::unique_ptr<PanelElement> nextMapButton = std::make_unique<NextMap>(Game::Instance().getTextureManager().getTexture("NextButton"), 0, 99, 88, (Vector2) {tablePos.x + width - 65 - 88, tablePos.y + (height - 99) / 2});
    std::unique_ptr<PanelElement> previousMapButton = std::make_unique<PreviousMap>(Game::Instance().getTextureManager().getTexture("PreviousButton"), 0, 99, 84, (Vector2) {tablePos.x + 75, tablePos.y + (height - 99) / 2});
    std::unique_ptr<PanelElement> ChooseMonkeyLaneButton = std::make_unique<ChooseMonkeyLane>(Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb"), 0, 360, 500, (Vector2) {tablePos.x + (width - 500) / 2, tablePos.y + (height - 360) / 2});
    std::unique_ptr<PanelElement> ChooseJungleButton = std::make_unique<ChooseJungle>(Game::Instance().getTextureManager().getTexture("JungleThumb"), 0, 360, 500, (Vector2) {tablePos.x + (width - 500) / 2, tablePos.y + (height - 360) / 2});
    std::unique_ptr<PanelElement> CommingSoonButton = std::make_unique<CommingSoon>(Game::Instance().getTextureManager().getTexture("CommingSoon2"), 0, 390, 392, (Vector2) {tablePos.x + (width - 392) / 2, tablePos.y + (height - 390) / 2});
    
    nextMapButtonPtr = nextMapButton.get();
    previousMapButtonPtr = previousMapButton.get();
    ChooseMonkeyLaneButtonPtr = ChooseMonkeyLaneButton.get();
    ChooseJungleButtonPtr = ChooseJungleButton.get();
    CommingSoonButtonPtr = CommingSoonButton.get();
    
    panel->addPanelElement(std::move(cancelMapSelectionButton));
    panel->addPanelElement(std::move(nextMapButton));
    panel->addPanelElement(std::move(previousMapButton));
    panel->addPanelElement(std::move(ChooseMonkeyLaneButton));
    panel->addPanelElement(std::move(ChooseJungleButton));
    panel->addPanelElement(std::move(CommingSoonButton));

    Font titleFont = Game::Instance().getFontManager().getFont("Big");
    int titleFontSize = 60;
    std::string titleText = "CHOOSE A MAP";
    Vector2 titleSize = MeasureTextEx(titleFont, titleText.c_str(), (float) titleFontSize, 1.0);

    std::unique_ptr<PanelElement> title = std::make_unique<TextField>(titleText, titleFont, WHITE, titleSize.y, titleSize.x, (Vector2) {tablePos.x + (width - titleSize.x) / 2, tablePos.y + 70});
    panel->addPanelElement(std::move(title));

    curMap = 0;
    previousMapButtonPtr->setAvailable(false);
    ChooseJungleButtonPtr->setAvailable(false);
    CommingSoonButtonPtr->setAvailable(false);
}

void MapSelectionState::draw() const {
    DrawTextureEx(background, {static_cast<float>((Properties::screenWidth - width) / 2), static_cast<float>((Properties::screenHeight - height) / 2)}, 0.0f, 2.0, WHITE);
    if(panel) panel->draw();
}

void MapSelectionState::update(Event::Type event) {
    switch (event) {
        case Event::Type::None:
            return;
        case Event::Type::MoveNext:
            curMap++;
            break;
        case Event::Type::MovePrevious:
            curMap--;
            break;
    }

    switch(curMap) {
        case 0:
            previousMapButtonPtr->setAvailable(false);
            //nextMapButtonPtr->setAvailable(true);
            ChooseMonkeyLaneButtonPtr->setAvailable(true);
            ChooseJungleButtonPtr->setAvailable(false);
            //CommingSoonButtonPtr->setAvailable(false);
            break;
        case 1:
            previousMapButtonPtr->setAvailable(true);
            nextMapButtonPtr->setAvailable(true);
            ChooseMonkeyLaneButtonPtr->setAvailable(false);
            ChooseJungleButtonPtr->setAvailable(true);
            CommingSoonButtonPtr->setAvailable(false);
            break;
        case 2:
            //previousMapButtonPtr->setAvailable(true);
            nextMapButtonPtr->setAvailable(false);
            //ChooseMonkeyLaneButtonPtr->setAvailable(false);
            ChooseJungleButtonPtr->setAvailable(false);
            CommingSoonButtonPtr->setAvailable(true);
            break;
    }
}