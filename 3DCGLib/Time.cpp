#include "Time.h"

namespace Lib
{
    // コンストラクタ
    Time::Time()
    {
        start = std::chrono::system_clock::now();
    }
    // デストラクタ
    Time::~Time()
    {
    }
    // DeltaTimeを返す
    float Time::getDeltaTime() const
    {
        auto end = std::chrono::system_clock::now();
        return std::chrono::duration<float, std::milli>(end - start).count();
    }
    // 開始からの経過時間
    float Time::getCurrentTime() const
    {
        return std::chrono::duration<float, std::milli>(start.time_since_epoch()).count();
    }
    // 引数で渡した時間が経過していればtrueを返す(ミリ秒)
    bool Time::timeOver(const float limit)
    {
        if (limit <= getDeltaTime()) {
            return true;
        }

        return false;
    }
    // 開始時間をリセット
    void Time::reset()
    {
        start = std::chrono::system_clock::now();
    }
}