#include "Timer.h"

Timer::Timer() = default;
Timer::~Timer() = default;

void Timer::reset() {
    lastTime = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

void Timer::setTime() {
    elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count()) - lastTime;
}

float Timer::getElapsedTime() const {
    return getElapsedTime();
}