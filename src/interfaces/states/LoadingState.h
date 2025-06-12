#ifndef LOADING_STATE_H
#define LOADING_STATE_H

#include <memory>
#include <thread>
#include <atomic>
#include <chrono>

#include "State.h"
#include "../../core/Game.h"

class LoadingState : public State {
private:
    bool startedLoading;

public:
    LoadingState();
    void setStartedLoading();
    bool getStartedLoading() const;
};

#endif // LOADING_STATE_H