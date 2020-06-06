//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    11/03/2020 18:19
// @project Horizon
//

#pragma once

#include "core/loop/Loop.hpp"
#include <thread>

namespace HORIZON::CORE::LOOP
{
    template<unsigned int TPS = 60>
    class FixTickLoop : public virtual Loop
    {
    public:
        FixTickLoop(Predicate const& predicate, LoopCallback const& callback, PreCallback const& preCallback = [] { }, PostCallback const& postCallback = [] { }) :
                Loop(predicate, callback, preCallback, postCallback)
        { }

        /*!
         * Gets the ticks per second of the loop.
         */
        [[nodiscard]] inline unsigned int TicksPerSecond() const
        { return TPS; }

    protected:
        void Wait(Loop::TimePoint loopStart) const final
        {
            // TODO: static might make problems with multiple (different) base loops?
            static Loop::DeltaTime TPSDuration(static_cast<Loop::DeltaTime::rep>(static_cast<double>(Loop::DeltaTime::period::den) / static_cast<double>(TPS)));
            std::this_thread::sleep_until(loopStart + TPSDuration);
        }
    };
}