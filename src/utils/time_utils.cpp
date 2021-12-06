#include <SDL2/SDL.h>

#include <thread>
#include <iostream>
#include <chrono>
#include <functional>
#include <future>

#include "time_utils.hpp"

// TIME UTILS CLASS
// TIME UTILS CLASS
// TIME UTILS CLASS

void TimeUtils::setTimeout() { }

void TimeUtils::setInterval(int interval, std::function<void()> callback) {
    if (TimeAccumulator::getAccumulatedTime() > interval) {
        callback();
        TimeAccumulator::resetAccumulator();
    }
}

void TimeUtils::setIntervalThreaded(int interval, std::function<void()> callback) {
    
    std::thread([callback, interval]() { 
        while (true) { 
            auto waitTill = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            callback();
            std::this_thread::sleep_until(waitTill);
        }
    }).detach();
    
};

void TimeUtils::setIntervalAsync(int interval, std::function<void()> callback) {

    std::future<void> fut = std::async([]() {
        std::cout << "TEST TEST TEST";
    });

    std::future<void>* test; 
    std::async([](int x) {}, 2);

};

// TIME ACCUMULATOR CLASS
// TIME ACCUMULATOR CLASS
// TIME ACCUMULATOR CLASS

int initialPoll = SDL_GetTicks();
int TimeAccumulator::timeOfLastPoll = initialPoll;

int TimeAccumulator::getAccumulatedTime() {
    int newPoll = SDL_GetTicks();
    return newPoll - timeOfLastPoll;
}

void TimeAccumulator::resetAccumulator() {
    int newPoll = SDL_GetTicks();
    TimeAccumulator::timeOfLastPoll = newPoll;
}