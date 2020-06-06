//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    11/03/2020 18:02
// @project Horizon
//

#include "core/loop/Loop.hpp"

#include <utility>


using namespace HORIZON::CORE::LOOP;
using namespace HORIZON::TIME;

Loop::Loop(Predicate predicate, LoopCallback callback, PreCallback preCallback, PostCallback postCallback) :
        _predicate(std::move(predicate)),
        _loopCallback(std::move(callback)),
        _preCallback(std::move(preCallback)),
        _postCallback(std::move(postCallback)),
        _terminate(false)
{ }


void Loop::Run()
{
    _preCallback();

    Clock::TimePointType lastTick = Clock::Now(),
                         temp;

    while (!_terminate && _predicate())
    {
        temp = Clock::Now();
        _loopCallback(temp - lastTick);
        lastTick = temp;

        Wait(temp);
    }

    _postCallback();
}


void Loop::Terminate()
{
    _terminate = true;
}