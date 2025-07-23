#include "GameState.h"
#include "../../core/Game.h"
#include <fstream>

GameState::GameState() : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("GameStateBackground")) { 
    curTowerType = 0;
    panel = std::make_unique<Panel>();
    Vector2 SGBPos = {1000, 720 - 59};    
    
    round = std::make_shared<TextField>("Round:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {5, 875});
    mode = std::make_shared<TextField>("Mode:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {320, 875});
    lives = std::make_shared<TextField>("200", Game::Instance().getFontManager().getFont("Medium"), RED, 30, 0, (Vector2) {1000 + 60, 10 + 5});
    cash = std::make_shared<TextField>("340", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 30, 0, (Vector2) {1000 + 60, 10 + 40 + 10});
    panel->addPanelElement((round));
    panel->addPanelElement((mode));
    panel->addPanelElement((lives));
    panel->addPanelElement((cash));
    
    std::shared_ptr<PanelElement> hpIcon = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("HP"), 40, 39, (Vector2) {1000 + 10, 10});
    std::shared_ptr<PanelElement> cashIcon = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("Cash"), 40, 42, (Vector2) {1000 + 10, 10 + 40 + 5});
    panel->addPanelElement((hpIcon));
    panel->addPanelElement((cashIcon));
    
    Vector2 towerBoxPos = {1000, 145};
    previousTowerButton = std::make_shared<PreviousTower>(Game::Instance().getTextureManager().getTexture("PreviousUpButton"), 0, 42, 50, (Vector2) {1000 + (200 - 50) / 2, towerBoxPos.y - 42 - 5});
    Texture boxTex = Game::Instance().getTextureManager().getTexture("Box");
    std::shared_ptr<PanelElement> boxes = std::make_shared<TextureField>(103, 100, towerBoxPos);
    for(int i = 0; i < 10; i++) {
        static_cast<TextureField*>(boxes.get())->addTexture({boxTex, towerBoxPos});
        if(i % 2 == 0) {
            towerBoxPos.x += 100;
        } else {
            towerBoxPos.x -= 100;
            towerBoxPos.y += 103;
        }
    }
    panel->addPanelElement((boxes));

    std::shared_ptr<PanelElement> startRoundButton = std::make_shared<StartRound>(Game::Instance().getTextureManager().getTexture("Start"), 0, 88, 88, (Vector2) {1000, 720});
    std::shared_ptr<PanelElement> gameOptionsButton = std::make_shared<GameOptions>(Game::Instance().getTextureManager().getTexture("Setting"), 0, 88, 88, (Vector2) {1000 + 88 + 5, 720});
    nextTowerButton = std::make_shared<NextTower>(Game::Instance().getTextureManager().getTexture("NextDownButton"), 0, 42, 50, (Vector2) {1000 + (200 - 50) / 2, towerBoxPos.y - 5});
    std::shared_ptr<PanelElement> fastForwardButton = std::make_shared<FastForward>(Game::Instance().getTextureManager().getTexture("FastForward"), 0, 88, 88, (Vector2) {1000, 720 + 88 + 4});
    std::shared_ptr<PanelElement> homeButton = std::make_shared<ToAreYouSure>(Game::Instance().getTextureManager().getTexture("Home"), 0, 88, 88, (Vector2) {1000 + 88 + 5, 720 + 88 + 4});
    previousTowerButton->setAvailable(false);
    panel->addPanelElement(startRoundButton);
    panel->addPanelElement(gameOptionsButton);
    panel->addPanelElement(previousTowerButton);    
    panel->addPanelElement(nextTowerButton);
    panel->addPanelElement(fastForwardButton);
    panel->addPanelElement(homeButton);

    towerBoxPos = {1000, 145};
    for(int i = 0; i < maxTowerTypes; i++) {
        chooseTowerButton[i] = std::make_shared<ChooseBombTower>(Game::Instance().getTextureManager().getTexture("BombTowerIcon"), 1, 103, 100, towerBoxPos);
        towerCost[i] = std::make_shared<TextField>("$1000", Game::Instance().getFontManager().getFont("SmallBold"), WHITE, 20, 100, (Vector2) {towerBoxPos.x + 20, towerBoxPos.y + 103 - 30});
        towerInfoButton[i] = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 25, 25, (Vector2) {towerBoxPos.x + 100 - 25, towerBoxPos.y});
        if(i >= 10) {
            chooseTowerButton[i]->setAvailable(false);
            towerCost[i]->setAvailable(false);
            towerInfoButton[i]->setAvailable(false);
        }
        panel->addPanelElement(chooseTowerButton[i]);
        panel->addPanelElement(towerCost[i]);
        panel->addPanelElement(towerInfoButton[i]);

        if(i % 2 == 0) {
            towerBoxPos.x += 100;
        } else {
            towerBoxPos.x -= 100;
            towerBoxPos.y += 103;
        }
        if(i == 9) towerBoxPos = {1000, 145};
    }
    
    movableTowerTexture = std::make_shared<MovableTextureField>(Game::Instance().getTextureManager().getTexture("DartMonkeyIcon"), 100, 103);
    panel->addPanelElement(movableTowerTexture);
    movableTowerTexture->setAvailable(false);
    infoTextbox = std::make_shared<MovableTextbox>("", Game::Instance().getFontManager().getFont("Small"), WHITE, 20, 125);
    panel->addPanelElement(infoTextbox);

    // Temporary only
    Game::Instance().getGameLogic().init();

    // Tower Detail
    // towerDetailPanel = std::make_unique<Panel>();
    // towerDetail = std::make_shared<TextField>("Detail", Game::Instance().getFontManager().getFont("Medium"), WHITE, 20, 0, (Vector2) {5, 755});
    // towerCost = std::make_shared<TextField>("Cost:", Game::Instance().getFontManager().getFont("Medium"), WHITE, 20, 0, (Vector2) {800, 725});
    // towerDetailPanel->addPanelElement((towerName));
    // towerDetailPanel->addPanelElement((towerDetail));
    // towerDetailPanel->addPanelElement((towerCost));
    // towerDetailPanel->setAvailable(false);
    
    // Tower Upgrade
    towerName = std::make_shared<TextField>("Name", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {5, 725});
    towerPanel = std::make_unique<Panel>();
    std::shared_ptr<PanelElement> priorityContainer = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("PurpleRect"), 115, 195, (Vector2) {5, 725 + 25 + 5});
    std::string priorityText = "First";
    Font smallFont = Game::Instance().getFontManager().getFont("SmallBold");
    float textWidth = MeasureTextEx(smallFont, priorityText.c_str(), 20, 1).x;
    priorityTitle = std::make_shared<TextField>(priorityText, smallFont, WHITE, 20, 0, (Vector2) {5 + (195 - textWidth) / 2, 875 - 5 - 15 - 20});
    towerTex = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("DartMonkeyUI"), 100, 100, (Vector2) {5 + (195 - 100) / 2, 725 + 25 + 5});
    towerPanel->addPanelElement(priorityContainer);
    towerPanel->addPanelElement(towerName);
    towerPanel->addPanelElement(towerTex);   
    towerPanel->addPanelElement(priorityTitle);

    std::shared_ptr<PanelElement> nextPriorityButton = std::make_shared<NextPriority>(Game::Instance().getTextureManager().getTexture("RightWhiteTriangle"), 1, 50, 23, (Vector2) {5 + 195 - 23 - 25, 875 - 5 - 50});
    std::shared_ptr<PanelElement> previousPriorityButton = std::make_shared<PreviousPriority>(Game::Instance().getTextureManager().getTexture("LeftWhiteTriangle"), 1, 50, 23, (Vector2) {5 + 20, 875 - 5 - 50});
    towerPanel->addPanelElement(nextPriorityButton);
    towerPanel->addPanelElement(previousPriorityButton);

    // 1200 - 195 - 10 - 250 * 3 = 45
    for(int i = 0; i < 3; i++) {
        std::shared_ptr<PanelElement> upgradeContainer = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("GreenRect"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i, 725 + 25 + 5});
        upgradeTex[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("CrossbowMasterUpgradeIcon"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i, 725 + 25 + 5});
        upgradeTitle[i] = std::make_shared<TextField>("Not Upgraded", Game::Instance().getFontManager().getFont("SupperSmallBold"), WHITE, 20, 100, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 2, 725 + 25 + 5});
        upgradeInfoButton[i] = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 25, 25, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 - 25, 725 + 25 + 5});
        towerPanel->addPanelElement(upgradeContainer);
        towerPanel->addPanelElement(upgradeTex[i]);
        towerPanel->addPanelElement(upgradeTitle[i]);
        towerPanel->addPanelElement(upgradeInfoButton[i]);
        
        std::shared_ptr<PanelElement> nextUpgradeContainer = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("RedRect"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        nextUpgradeButton[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("CrossbowMasterUpgradeIcon"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        nextUpgradeTitle[i] = std::make_shared<TextField>("Crossbow Master", Game::Instance().getFontManager().getFont("SupperSmallBold"), WHITE, 20, 100, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 + 2, 725 + 25 + 5});
        nextUpgradeCost[i] = std::make_shared<TextField>("Cost: $1000", Game::Instance().getFontManager().getFont("Small"), YELLOW, 20, 120, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 + 2, 725 + 25 + 5 + 115 - 20});
        nextUpgradeInfoButton[i] = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 25, 25, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 + 125 - 25 , 725 + 25 + 5});
        towerPanel->addPanelElement(nextUpgradeContainer);
        towerPanel->addPanelElement(nextUpgradeButton[i]);
        towerPanel->addPanelElement(nextUpgradeTitle[i]);
        towerPanel->addPanelElement(nextUpgradeCost[i]);
        towerPanel->addPanelElement(nextUpgradeInfoButton[i]);
    }
    
}

void GameState::draw() const {    
    // Update session 
    Game::Instance().getGameLogic().update();
    
    // Draw
    DrawTextureEx(background, (Vector2) {0, 0}, 0.0, 1.0, (Color) {140, 140, 140, 255});
    Game::Instance().getGameLogic().draw();
    std::dynamic_pointer_cast<MovableTextureField>(movableTowerTexture)->drawRangeCircle(100, {255, 255, 255, 128});
    
    //if(towerDetailPanel) towerDetailPanel->draw();
    if(towerPanel) towerPanel->draw();
    if(panel) panel->draw();
}

void GameState::update(Event::Type event) {
    switch(event) {
        case Event::Type::MoveNext:
            for(int i = curTowerType; i < curTowerType + 10; i++) {
                chooseTowerButton[i]->setAvailable(false);
                towerCost[i]->setAvailable(false);
                towerInfoButton[i]->setAvailable(false);
                if(i + 10 < maxTowerTypes) {
                    chooseTowerButton[i + 10]->setAvailable(true);
                    towerCost[i + 10]->setAvailable(true);
                    towerInfoButton[i + 10]->setAvailable(true);
                }
            }
            curTowerType += 10;
            break;
        case Event::Type::MovePrevious:
            for(int i = curTowerType; i < curTowerType + 10; i++) {
                if(i < maxTowerTypes) {
                    chooseTowerButton[i]->setAvailable(false);
                    towerCost[i]->setAvailable(false);
                    towerInfoButton[i]->setAvailable(false);
                }
                chooseTowerButton[i - 10]->setAvailable(true);
                towerCost[i - 10]->setAvailable(true);
                towerInfoButton[i - 10]->setAvailable(true);
            }
            curTowerType -= 10;
            break;
        case Event::Type::NextPriority:
            curPriority = (curPriority + 1) % 4; 
            break;
        case Event::Type::PreviousPriority:
            curPriority = (curPriority - 1 + 4) % 4;
            break;
        case Event::Type::HoveringInfo:
            infoTextbox->setAvailable(true);
            std::dynamic_pointer_cast<MovableTextbox>(infoTextbox)->setText("I don't know what to set here, so i just set nothing to it");
            break;
        default:
            if(Event::Type::HoveringChooseBomb <= event && event <= Event::Type::HoveringChooseBomb) {
                std::dynamic_pointer_cast<TextField>(towerName)->setText("Bomb");
            } else if(Event::Type::ClickedChooseBomb <= event && event <= Event::Type::ClickedChooseBomb) {
                movableTowerTexture->setAvailable(true);
                std::dynamic_pointer_cast<MovableTextureField>(movableTowerTexture)->setTexture(Game::Instance().getTextureManager().getTexture("BombTowerIcon"), 0);
            } else {
                std::dynamic_pointer_cast<TextField>(towerName)->setText("Name");
            }

            break;
    }
    previousTowerButton->setAvailable(curTowerType - 10 >= 0);
    nextTowerButton->setAvailable(curTowerType + 10 < maxTowerTypes);
    setPriority(static_cast<TargetPriority>(curPriority));
    
}

void GameState::handleInput() {
    State::handleInput();
    if(IsKeyPressed(KEY_ESCAPE)) {
        std::dynamic_pointer_cast<MovableTextureField>(movableTowerTexture)->setAvailable(false);
    }    

    // Info
    towerPanel->handleInput();

    // Handle Infobox
    bool drawInfobox = false;
    for(int i = 0; i < 3; i++) {
        if(std::dynamic_pointer_cast<Button>(upgradeInfoButton[i])->getState() != Button::State::None) drawInfobox = true;
        if(std::dynamic_pointer_cast<Button>(nextUpgradeInfoButton[i])->getState() != Button::State::None) drawInfobox = true;
    }
    for(int i = 0; i < maxTowerTypes; i++) {
        if(std::dynamic_pointer_cast<Button>(towerInfoButton[i])->getState() != Button::State::None) drawInfobox = true;
    }
    infoTextbox->setAvailable(drawInfobox);
}

void GameState::setPriority(TargetPriority type) {
    std::shared_ptr<PanelElement> priorityContainer = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("PurpleRect"), 115, 195, (Vector2) {20, 725 + 25 + 5});
    std::string priorityText = "";
    Font smallFont = Game::Instance().getFontManager().getFont("SmallBold");
    switch(type) {
        case TargetPriority::First:
            priorityText = "First";
            break;
        case TargetPriority::Last:
            priorityText = "Last";
            break;
        case TargetPriority::Close:
            priorityText = "Close";
            break;
        case TargetPriority::Strong:
            priorityText = "Strong";
            break;
    }
    
    float textWidth = MeasureTextEx(smallFont, priorityText.c_str(), 20, 1).x;
    std::dynamic_pointer_cast<TextField>(priorityTitle)->setTextAndPos(priorityText, (Vector2) {5 + (195 - textWidth) / 2, 875 - 5 - 15 - 20});
}
