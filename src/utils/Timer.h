#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include "raylib.h"

class Timer {
public:
    Timer();
    ~Timer();

    // Reset the timer to the current time
    void reset();

    // Create new elapsed time since last reset
    void setTime();

    // Get the elapsed time since last reset
    float getElapsedTime() const;

private:
    float lastTime; // Last recorded time
    float elapsedTime; // Elapsed time since last reset
};

#endif // TIMER_H