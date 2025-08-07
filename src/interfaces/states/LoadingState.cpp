#include "LoadingState.h"
#include "../../core/Game.h"

#include <algorithm>

LoadingState::LoadingState() : State(900, 1200, Game::Instance().getTextureManager().getTexture("LoadingStateBackground")) {
}

void LoadingState::draw() const {
    DrawTextureEx(background, (Vector2) {0, 0}, 0.0, 1.0, WHITE);
    
    DrawRectangle((width - 600) / 2, 850, 600, 20, LIGHTGRAY);
    DrawRectangle((width - 600) / 2, 850, Game::Instance().isLoadingDone() ? 600 : std::min(600.0, GetTime() * 400), 20, WHITE);
    Font font = Game::Instance().getFontManager().getFont("LoadingStateFont");
    float textWidth = MeasureTextEx(font, "Loading Assets...", 30, 0).x;
    std::shared_ptr<PanelElement> loadingText = std::make_shared<TextField>("Loading Assets...", font, WHITE, 30, 0, (Vector2) {(width - textWidth) / 2, 850 - 30});
    loadingText->draw();
    if(panel) panel->draw();
}

void LoadingState::update(Event::Type event)
{
}
