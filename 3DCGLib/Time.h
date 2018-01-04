#pragma once
#ifndef TIME_H
#define TIME_H

#include <chrono>

namespace Lib
{
    class Time
    {
    public:
        Time();
        ~Time();
        float getDeltaTime() const;
        float getCurrentTime() const;
        bool timeOver(const float limit);
        void reset();

    private:
        std::chrono::time_point<std::chrono::system_clock> start;
    };
}

#endif