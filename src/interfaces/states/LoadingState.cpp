#include "LoadingState.h"

LoadingState::LoadingState()
    : State(Properties::screenHeight, Properties::screenWidth, background), startedLoading(false){
}

void LoadingState::setStartedLoading() {
    startedLoading = true;
}

bool LoadingState::getStartedLoading() const {
    return startedLoading;
}
