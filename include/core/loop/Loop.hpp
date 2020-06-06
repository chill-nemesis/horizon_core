//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    11/03/2020 17:55
// @project Horizon
//


#pragma once

#include <functional>
#include <time/Clock.hpp>

namespace HORIZON::CORE::LOOP
{
    // Bröther, give me lööps

    class Loop
    {
    public:
        using DeltaTime = TIME::Clock::DurationType;
        using Predicate = std::function<bool()>;
        using LoopCallback = std::function<void(DeltaTime)>;
        using PreCallback = std::function<void(void)>;
        using PostCallback = std::function<void(void)>;

    protected:
        using TimePoint = TIME::Clock::TimePointType;

    private:
        Predicate    _predicate;
        LoopCallback _loopCallback;
        PreCallback  _preCallback;
        PostCallback _postCallback;
        bool         _terminate;


    public:
        /*!
         * The base loop.
         * Requires a predicate callback (stop condition) and a callback for each loop tick.
         */
        Loop(Predicate predicate, LoopCallback loopCallback, PreCallback preCallback = [] { }, PostCallback = [] { });

        /*!
         * Runs the loop.
         */
        virtual void Run();


        /*!
         * Terminates the loop without regard of the stop condition.
         * Note that this will not interrupt any wait but will only evaluate after the current call to Wait is over.
         */
        void Terminate();


    protected:
        virtual void Wait(TimePoint loopStart) const
        {/* per default: no wait */};
    };
}