#include "Time.h"

namespace Lib
{
    // �R���X�g���N�^
    Time::Time()
    {
        start = std::chrono::system_clock::now();
    }
    // �f�X�g���N�^
    Time::~Time()
    {
    }
    // DeltaTime��Ԃ�
    float Time::getDeltaTime() const
    {
        auto end = std::chrono::system_clock::now();
        return std::chrono::duration<float, std::milli>(end - start).count();
    }
    // �J�n����̌o�ߎ���
    float Time::getCurrentTime() const
    {
        return std::chrono::duration<float, std::milli>(start.time_since_epoch()).count();
    }
    // �����œn�������Ԃ��o�߂��Ă����true��Ԃ�(�~���b)
    bool Time::timeOver(const float limit)
    {
        if (limit <= getDeltaTime()) {
            return true;
        }

        return false;
    }
    // �J�n���Ԃ����Z�b�g
    void Time::reset()
    {
        start = std::chrono::system_clock::now();
    }
}