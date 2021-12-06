#pragma once 
#include <functional>
#include <thread>

class TimeUtils {

    public:

        static void setTimeout();

        static void setInterval(int interval, std::function<void()> callback);

        static void setIntervalThreaded(int interval, std::function<void()> callback);
        
        static void setIntervalAsync(int interval, std::function<void()> callback);

};

class TimeAccumulator {

    public:

        static int getAccumulatedTime();

        static void resetAccumulator();

    private:

        static int timeOfLastPoll;

};