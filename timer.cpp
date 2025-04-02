#include <GLFW/glfw3.h>
#include <iostream>

#include "timer.h"

namespace game {

Timer::Timer(void): end_time_(0.0f)
{
}


Timer::~Timer(void)
{
}


void Timer::Start(float duration)
{
    end_time_ = glfwGetTime() + duration;
}


bool Timer::Finished(void) const
{
    return (glfwGetTime() >= end_time_);
}

} // namespace game
