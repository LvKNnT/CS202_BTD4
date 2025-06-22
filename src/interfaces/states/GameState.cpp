#include "GameState.h"
#include "../../core/Game.h"

GameState::GameState() : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("GameStateBackground")) { 
    panel = std::make_unique<Panel>();
    Vector2 SGBPos = {1000, 720 - 59};    
    
    std::unique_ptr<PanelElement> towerName = std::make_unique<TextField>("Name", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 25, 0, (Vector2) {20, 730});
    std::unique_ptr<PanelElement> towerDetail = std::make_unique<TextField>("Detail", Game::Instance().getFontManager().getFont("Medium"), WHITE, 20, 0, (Vector2) {20, 760});
    std::unique_ptr<PanelElement> towerCost = std::make_unique<TextField>("Cost:", Game::Instance().getFontManager().getFont("Medium"), WHITE, 20, 0, (Vector2) {800, 730});
    std::unique_ptr<PanelElement> cantAffordTower = std::make_unique<TextField>("Can't Afford", Game::Instance().getFontManager().getFont("Medium"), RED, 25, 0, (Vector2) {680, 730});
    std::unique_ptr<PanelElement> round = std::make_unique<TextField>("Round:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {20, 875});
    std::unique_ptr<PanelElement> mode = std::make_unique<TextField>("Mode:", Game::Instance().getFontManager().getFont("Medium"), ORANGE, 25, 0, (Vector2) {320, 875});
    std::unique_ptr<PanelElement> hp = std::make_unique<TextField>("200", Game::Instance().getFontManager().getFont("Medium"), RED, 30, 0, (Vector2) {1000 + 60, 10 + 5});
    std::unique_ptr<PanelElement> cash = std::make_unique<TextField>("340", Game::Instance().getFontManager().getFont("Medium"), YELLOW, 30, 0, (Vector2) {1000 + 60, 10 + 40 + 10});
    panel->addPanelElement(std::move(towerName));
    panel->addPanelElement(std::move(towerDetail));
    panel->addPanelElement(std::move(towerCost));
    panel->addPanelElement(std::move(cantAffordTower));
    panel->addPanelElement(std::move(round));
    panel->addPanelElement(std::move(mode));
    panel->addPanelElement(std::move(hp));
    panel->addPanelElement(std::move(cash));
    
    std::unique_ptr<PanelElement> hpIcon = std::make_unique<TextureField>(Game::Instance().getTextureManager().getTexture("HP"), 40, 39, (Vector2) {1000 + 10, 10});
    std::unique_ptr<PanelElement> cashIcon = std::make_unique<TextureField>(Game::Instance().getTextureManager().getTexture("Cash"), 40, 42, (Vector2) {1000 + 10, 10 + 40 + 5});
    panel->addPanelElement(std::move(hpIcon));
    panel->addPanelElement(std::move(cashIcon));
    
    Vector2 towerBoxPos = {1000, 145};
    Texture boxTex = Game::Instance().getTextureManager().getTexture("Box");
    std::unique_ptr<PanelElement> towers = std::make_unique<TextureField>(103, 100, towerBoxPos);
    for(int i = 0; i < 10; i++) {
        static_cast<TextureField*>(towers.get())->addTexture({boxTex, towerBoxPos});
        if(i % 2 == 0) {
            towerBoxPos.x += 100;
        } else {
            towerBoxPos.x -= 100;
            towerBoxPos.y += 103;
        }
    }
    towerBoxPos = {1000, 145};
    std::unique_ptr<PanelElement> previousTowerButton = std::make_unique<PreviousTower>(Game::Instance().getTextureManager().getTexture("PreviousUpButton"), 0, 42, 50, (Vector2) {1000 + (200 - 50) / 2, towerBoxPos.y - 42 - 5});
    for(int i = 0; i < 10; i++) {
        static_cast<TextureField*> (towers.get())->addTexture({Game::Instance().getTextureManager().getTexture("BombTowerIcon"), towerBoxPos});
        if(i % 2 == 0) {
            towerBoxPos.x += 100;
        } else {
            towerBoxPos.x -= 100;
            towerBoxPos.y += 103;
        }
    }
    panel->addPanelElement(std::move(towers));
    
    std::unique_ptr<PanelElement> startRoundButton = std::make_unique<StartRound>(Game::Instance().getTextureManager().getTexture("Start"), 0, 88, 88, (Vector2) {1000, 720});
    std::unique_ptr<PanelElement> gameOptionsButton = std::make_unique<GameOptions>(Game::Instance().getTextureManager().getTexture("Setting"), 0, 88, 88, (Vector2) {1000 + 88 + 5, 720});
    std::unique_ptr<PanelElement> nextTowerButton = std::make_unique<NextTower>(Game::Instance().getTextureManager().getTexture("NextDownButton"), 0, 42, 50, (Vector2) {1000 + (200 - 50) / 2, towerBoxPos.y - 5});
    std::unique_ptr<PanelElement> fastForwardButton = std::make_unique<FastForward>(Game::Instance().getTextureManager().getTexture("FastForward"), 0, 88, 88, (Vector2) {1000, 720 + 88 + 4});
    std::unique_ptr<PanelElement> homeButton = std::make_unique<CancelCurrentState>(Game::Instance().getTextureManager().getTexture("Home"), 0, 88, 88, (Vector2) {1000 + 88 + 5, 720 + 88 + 4});
    panel->addPanelElement(std::move(startRoundButton));
    panel->addPanelElement(std::move(gameOptionsButton));
    panel->addPanelElement(std::move(previousTowerButton));
    panel->addPanelElement(std::move(nextTowerButton));
    panel->addPanelElement(std::move(fastForwardButton));
    panel->addPanelElement(std::move(homeButton));
}

void GameState::draw() const {
    DrawTextureEx(background, (Vector2) {0, 0}, 0.0, 1.0, (Color) {140, 140, 140, 255});
    DrawTextureEx(Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb"), (Vector2) {0, 0}, 0.0, 1.0, WHITE);
    panel->draw();
}