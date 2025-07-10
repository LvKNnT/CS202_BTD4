#include "GameState.h"
#include "../../core/Game.h"
#include <fstream>

GameState::GameState() : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("GameStateBackground")) { 
    curTowerType = 0;
    panel = std::make_unique<Panel>();
    Vector2 SGBPos = {1000, 720 - 59};    
    
    towerName = std::make_shared<TextField>("Name", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {20, 730});
    towerDetail = std::make_shared<TextField>("Detail", Game::Instance().getFontManager().getFont("Medium"), WHITE, 20, 0, (Vector2) {20, 760});
    towerCost = std::make_shared<TextField>("Cost:", Game::Instance().getFontManager().getFont("Medium"), WHITE, 20, 0, (Vector2) {800, 730});
    cantAffordTower = std::make_shared<TextField>("Can't Afford", Game::Instance().getFontManager().getFont("Medium"), RED, 25, 0, (Vector2) {680, 730});
    round = std::make_shared<TextField>("Round:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {20, 875});
    mode = std::make_shared<TextField>("Mode:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {320, 875});
    hp = std::make_shared<TextField>("200", Game::Instance().getFontManager().getFont("Medium"), RED, 30, 0, (Vector2) {1000 + 60, 10 + 5});
    cash = std::make_shared<TextField>("340", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 30, 0, (Vector2) {1000 + 60, 10 + 40 + 10});
    panel->addPanelElement((towerName));
    panel->addPanelElement((towerDetail));
    panel->addPanelElement((towerCost));
    panel->addPanelElement((cantAffordTower));
    panel->addPanelElement((round));
    panel->addPanelElement((mode));
    panel->addPanelElement((hp));
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
        if(i >= 10) chooseTowerButton[i]->setAvailable(false);
        panel->addPanelElement(chooseTowerButton[i]);

        if(i % 2 == 0) {
            towerBoxPos.x += 100;
        } else {
            towerBoxPos.x -= 100;
            towerBoxPos.y += 103;
        }
        if(i == 9) towerBoxPos = {1000, 145};
    }
    
    movableTowerTexture = std::make_shared<MovableTextureField>(Game::Instance().getTextureManager().getTexture("BombTowerIcon"), 100, 103);
    panel->addPanelElement(movableTowerTexture);
    movableTowerTexture->setAvailable(false);

    // Temporary only
    Game::Instance().getGameLogic().init();
}

void GameState::draw() const {
    DrawTextureEx(background, (Vector2) {0, 0}, 0.0, 1.0, (Color) {140, 140, 140, 255});
    DrawTextureEx(Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb"), (Vector2) {0, 0}, 0.0, 1.0, WHITE);
    std::dynamic_pointer_cast<MovableTextureField>(movableTowerTexture)->drawRangeCircle(100, {255, 255, 255, 128});
    panel->draw();

    // Temporary only
    Game::Instance().getGameLogic().update();
    Game::Instance().getGameLogic().draw();
}

void GameState::update(Event::Type event) {
    switch(event) {
        case Event::Type::MoveNext:
            for(int i = curTowerType; i < curTowerType + 10; i++) {
                chooseTowerButton[i]->setAvailable(false);
                if(i + 10 < maxTowerTypes) chooseTowerButton[i + 10]->setAvailable(true);
            }
            curTowerType += 10;
            break;
        case Event::Type::MovePrevious:
            for(int i = curTowerType; i < curTowerType + 10; i++) {
                if(i < maxTowerTypes) chooseTowerButton[i]->setAvailable(false);
                chooseTowerButton[i - 10]->setAvailable(true);
            }
            curTowerType -= 10;
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
}

void GameState::handleInput() {
    State::handleInput();
    if(IsKeyPressed(KEY_ESCAPE)) {
        std::dynamic_pointer_cast<MovableTextureField>(movableTowerTexture)->setAvailable(false);
    }
}
