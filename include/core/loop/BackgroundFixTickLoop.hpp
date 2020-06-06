//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    30/03/2020 16:51
// @project Horizon
//


#pragma once

#include "core/loop/BackgroundLoop.hpp"
#include "core/loop/FixTickLoop.hpp"

namespace HORIZON::CORE::LOOP
{
    template<unsigned int TPS = 60>
    class BackgroundFixTickLoop : public BackgroundLoop, public FixTickLoop<TPS>
    {
    public:
        using Predicate = Loop::Predicate;
        using Callback = Loop::LoopCallback;

        BackgroundFixTickLoop(Predicate const& predicate, Callback const& callback, PreCallback const& preCallback = [] { }, PostCallback const& postCallback = [] { }) :
                Loop(predicate, callback, preCallback, postCallback),
                BackgroundLoop(predicate, callback, preCallback, postCallback),
                FixTickLoop<TPS>(predicate, callback, preCallback, postCallback)
        { }
    };
}