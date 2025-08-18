#include "GameState.h"
#include "../../core/Game.h"
#include "../../interfaces/audio/MyAudio.h"
#include "../../logic/mode/RoundInfo.h"

#include <fstream>

GameState::GameState() : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("GameStateBackground")) { 
    attach(Game::Instance().getStateManager());
    curTowerType = 0;
    panel = std::make_unique<Panel>();
    Vector2 SGBPos = {1000, 720 - 59};    
    
    std::string modeStr = DifficultyInfo::Instance().getDifficultyInfo(Game::Instance().getGameLogic().getDifficulty())["name"] + " - "
                        + ModeInfo::Instance().getModeInfo(Game::Instance().getGameLogic().getModeType())["name"];
    round = std::make_shared<TextField>("Round:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {5, 875});
    mode = std::make_shared<TextField>("Mode: " + modeStr, Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {320, 875});
    hero = std::make_shared<TextField>("Hero: " + Game::Instance().getGameLogic().getHeroInfo()["name"], Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {320 + 380, 875});
    lives = std::make_shared<TextField>("200", Game::Instance().getFontManager().getFont("Medium"), RED, 30, 0, (Vector2) {1000 + 60, 10 + 5});
    cash = std::make_shared<TextField>("340", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 30, 0, (Vector2) {1000 + 60, 10 + 40 + 10});
    panel->addPanelElement((round));
    panel->addPanelElement((mode));
    panel->addPanelElement((hero));
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

    std::shared_ptr<PanelElement> startRoundButton = std::make_shared<StartRoundButton>(Game::Instance().getTextureManager().getTexture("Start"), 0, 88, 88, (Vector2) {1000, 720});
    std::shared_ptr<PanelElement> gameOptionsButton = std::make_shared<GameOptions>(Game::Instance().getTextureManager().getTexture("Setting"), 0, 88, 88, (Vector2) {1000 + 88 + 5, 720});
    nextTowerButton = std::make_shared<NextTower>(Game::Instance().getTextureManager().getTexture("NextDownButton"), 0, 42, 50, (Vector2) {1000 + (200 - 50) / 2, towerBoxPos.y - 5});
    std::shared_ptr<PanelElement> fastForwardButton = std::make_shared<FastForward>(Game::Instance().getTextureManager().getTexture("FastForward"), 0, 88, 88, (Vector2) {1000, 720 + 88 + 4});
    std::shared_ptr<PanelElement> homeButton = std::make_shared<ToAreYouSure>(Game::Instance().getTextureManager().getTexture("Home"), 0, 88, 88, (Vector2) {1000 + 88 + 5, 720 + 88 + 4});
    previousTowerButton->setAvailable(false);
    nextTowerButton->setAvailable(false);
    panel->addPanelElement(startRoundButton);
    panel->addPanelElement(gameOptionsButton);
    panel->addPanelElement(previousTowerButton);    
    panel->addPanelElement(nextTowerButton);
    panel->addPanelElement(fastForwardButton);
    panel->addPanelElement(homeButton);

    towerBoxPos = {1000, 145};
    for(int i = 0; i < maxTowerTypes; i++) {
        if(i <= 7) {
            auto infos = Game::Instance().getGameLogic().getInfoTower(getTowerType(i));
            towerCost[i] = std::make_shared<TextField>('$' + infos["cost"], Game::Instance().getFontManager().getFont("SmallBold"), YELLOW, 20, 100, (Vector2) {towerBoxPos.x, towerBoxPos.y + 103 - 30});
            if(i == 0) chooseTowerButton[i] = std::make_shared<ChooseDartMonkeyTower>(Game::Instance().getTextureManager().getTexture(infos["name"] + " Icon"), 1, 103, 100, towerBoxPos);
            if(i == 1) chooseTowerButton[i] = std::make_shared<ChooseBombShooterTower>(Game::Instance().getTextureManager().getTexture(infos["name"] + " Icon"), 1, 103, 100, towerBoxPos);
            if(i == 2) chooseTowerButton[i] = std::make_shared<ChooseNinjaMonkeyTower>(Game::Instance().getTextureManager().getTexture(infos["name"] + " Icon"), 1, 103, 100, towerBoxPos);
            if(i == 3) chooseTowerButton[i] = std::make_shared<ChooseSniperMonkeyTower>(Game::Instance().getTextureManager().getTexture(infos["name"] + " Icon"), 1, 103, 100, towerBoxPos);
            if(i == 4) chooseTowerButton[i] = std::make_shared<ChooseIceMonkeyTower>(Game::Instance().getTextureManager().getTexture(infos["name"] + " Icon"), 1, 103, 100, towerBoxPos);
            if(i == 5) chooseTowerButton[i] = std::make_shared<ChooseMonkeySubTower>(Game::Instance().getTextureManager().getTexture(infos["name"] + " Icon"), 1, 103, 100, towerBoxPos);
        }
        // if(i > 5) {
        //     chooseTowerButton[i] = std::make_shared<ChooseBombShooterTower>(Game::Instance().getTextureManager().getTexture("Bomb Shooter Icon"), 1, 103, 100, towerBoxPos);
        //     towerCost[i] = std::make_shared<TextField>("$6969", Game::Instance().getFontManager().getFont("SmallBold"), WHITE, 20, 100, (Vector2) {towerBoxPos.x, towerBoxPos.y + 103 - 30});
        // }
        towerInfoButton[i] = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 25, 25, (Vector2) {towerBoxPos.x + 100 - 25, towerBoxPos.y});
        // if(i >= 10) {
        //     chooseTowerButton[i]->setAvailable(false);
        //     towerCost[i]->setAvailable(false);
        //     towerInfoButton[i]->setAvailable(false);
        // }
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
    
    upgradeInfoTextbox = std::make_shared<MovableTextbox>("", Game::Instance().getFontManager().getFont("Small"), WHITE, 20, 150);
    towerInfoTextbox = std::make_shared<MovableTextbox>("", Game::Instance().getFontManager().getFont("Small"), WHITE, 20, 150);
    towerInfoTextbox->setAvailable(false);
    upgradeInfoTextbox->setAvailable(false);
    panel->addPanelElement(upgradeInfoTextbox);
    panel->addPanelElement(towerInfoTextbox);
    
    // Round Info 
    roundPanel = std::make_unique<Panel>();
    std::string mapName = MapInfo::Instance().getMapInfo(Game::Instance().getGameLogic().getMapType())["name"];
    roundTitle = std::make_shared<TextField>(mapName, Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {5, 725});
    roundInfo = std::make_shared<TextField>(DifficultyInfo::Instance().getDifficultyInfo(Game::Instance().getGameLogic().getDifficulty())["description"], Game::Instance().getFontManager().getFont("Medium"), WHITE, 25, 900, (Vector2) {5, 725 + 25 + 10});
    roundPanel->addPanelElement(roundTitle);
    roundPanel->addPanelElement(roundInfo);

    // Tower Info
    towerPanel = std::make_unique<Panel>();
    towerName = std::make_shared<TextField>("Name", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {5, 725});
    towerPopCount = std::make_shared<TextField>("Pop Count: 0", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {5 + 550, 725});
    sellPrice = std::make_shared<TextField>("", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {5 + 300, 725});
    std::shared_ptr<PanelElement> sellTowerButton = std::make_shared<SellButton>(Game::Instance().getTextureManager().getTexture("GameStateButton"), 20, 25, 84, (Vector2) {5 + 360, 725});
    std::shared_ptr<PanelElement> priorityContainer = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("PurpleRect"), 115, 195, (Vector2) {5, 725 + 25 + 5});
    Font smallFont = Game::Instance().getFontManager().getFont("SmallBold");
    priorityTitle = std::make_shared<TextField>("", smallFont, WHITE, 20, 195, (Vector2) {5, 875 - 5 - 15 - 20});
    towerTex = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture(""), 100, 100, (Vector2) {5 + (195 - 100) / 2, 725 + 25 + 5});
    towerPanel->addPanelElement(priorityContainer);
    towerPanel->addPanelElement(towerName);
    towerPanel->addPanelElement(towerPopCount);
    towerPanel->addPanelElement(towerTex);   
    towerPanel->addPanelElement(priorityTitle);
    towerPanel->addPanelElement(sellPrice);
    towerPanel->addPanelElement(sellTowerButton);


    std::shared_ptr<PanelElement> nextPriorityButton = std::make_shared<NextPriority>(Game::Instance().getTextureManager().getTexture("RightWhiteTriangle"), 1, 50, 23, (Vector2) {5 + 195 - 23 - 25, 875 - 5 - 50});
    std::shared_ptr<PanelElement> previousPriorityButton = std::make_shared<PreviousPriority>(Game::Instance().getTextureManager().getTexture("LeftWhiteTriangle"), 1, 50, 23, (Vector2) {5 + 20, 875 - 5 - 50});
    towerPanel->addPanelElement(nextPriorityButton);
    towerPanel->addPanelElement(previousPriorityButton);

    // 1200 - 195 - 10 - 250 * 3 = 45
    for(int i = 0; i < 3; i++) {
        upgradeContainer[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("GreyRect"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i, 725 + 25 + 5});
        upgradeButton[i] = std::make_shared<NoUpgradeButton>(Game::Instance().getTextureManager().getTexture(""), 0, 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i, 725 + 25 + 5});
        upgradeTitle[i] = std::make_shared<TextField>("", Game::Instance().getFontManager().getFont("SupperSmallBold"), WHITE, 20, 90, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 2, 725 + 25 + 5});
        upgradeInfoButton[i] = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 25, 25, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 - 25, 725 + 25 + 5});
        towerPanel->addPanelElement(upgradeContainer[i]);
        towerPanel->addPanelElement(upgradeButton[i]);
        towerPanel->addPanelElement(upgradeTitle[i]);
        towerPanel->addPanelElement(upgradeInfoButton[i]);
        
        nextUpgradeContainer[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("GreenRect"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        redNextUpgradeContainer[i] = std::make_shared<TextureField>(Game::Instance().getTextureManager().getTexture("RedRect"), 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        if(i == 0) nextUpgradeButton[i] = std::make_shared<UpgradeLeftButton>(Game::Instance().getTextureManager().getTexture("CrossbowMasterUpgradeIcon"), 1, 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        if(i == 1) nextUpgradeButton[i] = std::make_shared<UpgradeMiddleButton>(Game::Instance().getTextureManager().getTexture("CrossbowMasterUpgradeIcon"), 1, 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        if(i == 2) nextUpgradeButton[i] = std::make_shared<UpgradeRightButton>(Game::Instance().getTextureManager().getTexture("CrossbowMasterUpgradeIcon"), 1, 115, 125, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125, 725 + 25 + 5});
        nextUpgradeTitle[i] = std::make_shared<TextField>("", Game::Instance().getFontManager().getFont("SupperSmallBold"), WHITE, 20, 90, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 + 2, 725 + 25 + 5});
        nextUpgradeCost[i] = std::make_shared<TextField>("Cost: $1000", Game::Instance().getFontManager().getFont("SupperSmallBold"), YELLOW, 20, /*120*/0, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 + 2, 725 + 25 + 5 + 115 - 20});
        nextUpgradeInfoButton[i] = std::make_shared<Info>(Game::Instance().getTextureManager().getTexture("Info"), 1, 25, 25, (Vector2) {5 + 195 + 15.f * (i + 1) + 250.f * i + 125 + 125 - 25 , 725 + 25 + 5});
        towerPanel->addPanelElement(nextUpgradeContainer[i]);
        towerPanel->addPanelElement(redNextUpgradeContainer[i]);
        towerPanel->addPanelElement(nextUpgradeButton[i]);
        towerPanel->addPanelElement(nextUpgradeTitle[i]);
        towerPanel->addPanelElement(nextUpgradeCost[i]);
        towerPanel->addPanelElement(nextUpgradeInfoButton[i]);
    }
    towerPanel->setAvailable(false);
}

void GameState::draw() const {    
    // Draw
    Game::Instance().getGameLogic().draw();
    DrawTextureEx(background, (Vector2) {0, 0}, 0.0, 1.0, (Color) {140, 140, 140, 255});
    
    if(towerPanel) towerPanel->draw();
    if(roundPanel) roundPanel->draw();
    if(panel) panel->draw();
}

void GameState::update(Event::Type event) {
    MySound upgradeSound("Upgrade");
    // Set info for ChooseTowerButton
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
            Game::Instance().getGameLogic().chooseNextPriority();
            std::dynamic_pointer_cast<TextField>(priorityTitle)->setText(Game::Instance().getGameLogic().getInfoTower()["targetPriority"]);
            break;
        case Event::Type::PreviousPriority:
            Game::Instance().getGameLogic().choosePreviousPriority();
            std::dynamic_pointer_cast<TextField>(priorityTitle)->setText(Game::Instance().getGameLogic().getInfoTower()["targetPriority"]);
            break;
        case Event::Type::HoveringInfo:
            upgradeInfoTextbox->setAvailable(true);
            break;
        case Event::Type::TickFastForward:
            Game::Instance().getGameLogic().activeTickFast();
            break;
        case Event::Type::UntickFastForward:
            Game::Instance().getGameLogic().unactiveTickFast();
            break;
        case Event::Type::ClickedChooseDartMonkey:
            clickedTowerType = TowerType::DartMonkey;
            break;
        case Event::Type::ClickedChooseBomb:
            clickedTowerType = TowerType::BombShooter;
            break;
        case Event::Type::ClickedChooseNinjaMonkey:
            clickedTowerType = TowerType::NinjaMonkey;
            break;
        case Event::Type::ClickedChooseSniperMonkey:
            clickedTowerType = TowerType::SniperMonkey;
            break;
        case Event::Type::ClickedChooseBoomerangMonkey:
            clickedTowerType = TowerType::BoomerangMonkey;
            break;
        case Event::Type::ClickedChooseTackShooter:
            clickedTowerType = TowerType::TackShooter;
            break;
        case Event::Type::ClickedChooseIceMonkey:
            clickedTowerType = TowerType::IceMonkey;
            break;
        case Event::Type::ClickedChooseMonkeySub:
            clickedTowerType = TowerType::MonkeySub;
            break;
        case Event::Type::UpgradeTowerLeft:
            if(Game::Instance().getGameLogic().upgradeTower(UpgradeUnits::Top)) upgradeSound.start();
            break;
        case Event::Type::UpgradeTowerMiddle:
            if(Game::Instance().getGameLogic().upgradeTower(UpgradeUnits::Middle)) upgradeSound.start();
            break;
        case Event::Type::UpgradeTowerRight:
            if(Game::Instance().getGameLogic().upgradeTower(UpgradeUnits::Bottom)) upgradeSound.start();
            break;
        case Event::Type::SellTower:
            Game::Instance().getGameLogic().sellTower();
            unpickTower();
            break;
        default:
            break;
        }
        
        previousTowerButton->setAvailable(curTowerType - 10 >= 0);
        nextTowerButton->setAvailable(curTowerType + 10 < maxTowerTypes);    
    }
    
void GameState::handleInput() {
    // update game logic
    
    Game::Instance().getGameLogic().update();
    gameEnd();

    auto preTowerType = clickedTowerType;
    State::handleInput();
    towerPanel->update();
    
    // Live Infos
    auto liveInfos = Game::Instance().getGameLogic().getInfoResource();
    std::dynamic_pointer_cast<TextField>(lives)->setText(liveInfos["lives"]);
    std::dynamic_pointer_cast<TextField>(cash)->setText(liveInfos["cash"]);
    std::dynamic_pointer_cast<TextField>(round)->setText("Round: " + liveInfos["currentRound"] + '/' + liveInfos["maxRound"]);
    // add game tip
    std::string roundInfoStr = RoundInfo::Instance().getRoundInfo(std::stoi(liveInfos["currentRound"]))["detail"];
    std::dynamic_pointer_cast<TextField>(roundInfo)->setText(roundInfoStr.empty() ? DifficultyInfo::Instance().getDifficultyInfo(Game::Instance().getGameLogic().getDifficulty())["description"] : roundInfoStr);

    // Escape Input
    if(IsKeyPressed(KEY_ESCAPE)) {
        if(clickedTowerType != TowerType::None) {
            clickedTowerType = TowerType::None;
            Game::Instance().getGameLogic().unPutTower();
        } 
        unpickTower();
        return;
    }    

    if(preTowerType == TowerType::None && clickedTowerType != TowerType::None) return;

    // Place towers
    if(clickedTowerType != TowerType::None) {
        Game::Instance().getGameLogic().putTower(clickedTowerType, GetMousePosition());
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if(Game::Instance().getGameLogic().spawnTower()) {
                MySound placingSound("Placing");
                placingSound.start();
                Game::Instance().getGameLogic().unPutTower();
                pickTower();
                clickedTowerType = TowerType::None;
            }
            return;
        }
    }
    
    // Draw current Tower Object Infos
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && Utils::isMouseInMap()) {
        pickTower();
        return;
    }
    
    // Upgrades
    for(int i = 0; i < 3; i++) {
        std::string upgradeType;
        if(i == 0) upgradeType = "Top";
        if(i == 1) upgradeType = "Middle";
        if(i == 2) upgradeType = "Bottom";
        auto nextUpgradeButtonPtr = std::dynamic_pointer_cast<UpgradeButton>(nextUpgradeButton[i]);
        auto upgradeButtonPtr = std::dynamic_pointer_cast<UpgradeButton>(upgradeButton[i]);
        
        auto infos = Game::Instance().getGameLogic().getInfoTower();
        std::dynamic_pointer_cast<TextField>(upgradeTitle[i])->setText(infos["name" + upgradeType]);
        std::dynamic_pointer_cast<UpgradeButton>(upgradeButton[i])->setTexture(Game::Instance().getTextureManager().getTexture(infos["name" + upgradeType]));
        std::dynamic_pointer_cast<TextField>(nextUpgradeCost[i])->setText("Cost: $" + infos["upgradeCost" + upgradeType]);
        std::dynamic_pointer_cast<TextField>(nextUpgradeTitle[i])->setText(infos["upgradeName" + upgradeType]);
        std::dynamic_pointer_cast<UpgradeButton>(nextUpgradeButton[i])->setTexture(Game::Instance().getTextureManager().getTexture(infos["upgradeName" + upgradeType]));
        
        if(Game::Instance().getGameLogic().isUpgradeTower(static_cast<UpgradeUnits>(i)) == false) {
            redNextUpgradeContainer[i]->setAvailable(true);
            nextUpgradeContainer[i]->setAvailable(false);
        } else {
            redNextUpgradeContainer[i]->setAvailable(false);
            nextUpgradeContainer[i]->setAvailable(true);
        }
        
        if(upgradeButtonPtr->getState() != Button::State::None) {
            std::dynamic_pointer_cast<TextField>(upgradeInfoTextbox)->setText(infos["description" + upgradeType]);
        }
        
        if(nextUpgradeButtonPtr->getState() != Button::State::None) {
            std::dynamic_pointer_cast<TextField>(upgradeInfoTextbox)->setText(infos["upgradeDescription" + upgradeType]);
        }
    }
    
    LogicInfo curTowerInfos = Game::Instance().getGameLogic().getInfoTower();
    if(towerPanel->getIsAvailable()) {
        std::dynamic_pointer_cast<TextField>(towerPopCount)->setText("Pop count: " + curTowerInfos["popCount"]);
    }
    
    // Handle Infobox
    bool drawUpgradeInfoBox = false;
    for(int i = 0; i < 3; i++) {
        if(std::dynamic_pointer_cast<Button>(upgradeInfoButton[i])->getState() != Button::State::None) drawUpgradeInfoBox = true;
        if(std::dynamic_pointer_cast<Button>(nextUpgradeInfoButton[i])->getState() != Button::State::None) drawUpgradeInfoBox = true;
    }
    upgradeInfoTextbox->setAvailable(drawUpgradeInfoBox && towerPanel->getIsAvailable());
    
    
    bool drawButtonInfoBox = false;
    for(int i = 0; i < maxTowerTypes; i++) {
        if(std::dynamic_pointer_cast<Button>(towerInfoButton[i])->getState() != Button::State::None) {
            auto infos = Game::Instance().getGameLogic().getInfoTower(getTowerType(i));
            std::dynamic_pointer_cast<MovableTextbox>(towerInfoTextbox)->setText(infos["description"]);
            drawButtonInfoBox = true;
            break;
        }
    }
    towerInfoTextbox->setAvailable(drawButtonInfoBox);
}

void GameState::pickTower() {
    Game::Instance().getGameLogic().pickTower(GetMousePosition());
    LogicInfo curTowerInfos = Game::Instance().getGameLogic().getInfoTower();
    if(!curTowerInfos["name"].empty()) {
        roundPanel->setAvailable(false);
        towerPanel->setAvailable(true);
        std::dynamic_pointer_cast<TextField>(towerName)->setText(curTowerInfos["name"]);
        std::dynamic_pointer_cast<TextureField>(towerTex)->setTexture(Game::Instance().getTextureManager().getTexture(curTowerInfos["name"] + " Info"));
        std::dynamic_pointer_cast<TextField>(priorityTitle)->setText(curTowerInfos["targetPriority"]);
        std::dynamic_pointer_cast<TextField>(sellPrice)->setText("$" + curTowerInfos["sellPrice"]);
    } else {
        unpickTower();
    }
}

void GameState::unpickTower() {
    Game::Instance().getGameLogic().unPickTower();
    if(towerPanel->getIsAvailable()) {
        roundPanel->setAvailable(true);
        towerPanel->setAvailable(false);
        upgradeInfoTextbox->setAvailable(false);
    }
}

TowerType GameState::getTowerType(int i) const {
    switch(i) {
        case 0:
            return TowerType::DartMonkey;
        case 1:
            return TowerType::BombShooter;
        case 2: 
            return TowerType::NinjaMonkey;
        case 3:
            return TowerType::SniperMonkey;
        case 4:
            return TowerType::IceMonkey;
        case 5:
            return TowerType::MonkeySub;
    }
    return TowerType::None;
}

void GameState::gameEnd(){
    int endState = Game::Instance().getGameLogic().isEndGame();
    if(endState == -1) {
        notify(Event::Type::ToGameOver);
    } else if(endState == 1) {
        notify(Event::Type::ToVictory);
    }
}

void GameState::attach(std::shared_ptr<IObserver> observer) {
    observers.push_back(observer);
}

void GameState::detach(std::shared_ptr<IObserver> observer) {
    observers.remove(observer);
}

void GameState::notify(Event::Type event) {
    for(auto observer:observers) observer->update(event);
}
