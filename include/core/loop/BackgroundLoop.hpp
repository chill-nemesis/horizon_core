//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    30/03/2020 16:27
// @project Horizon
//


#pragma once

#include "core/loop/Loop.hpp"
#include <parallel/Worker.hpp>

namespace HORIZON::CORE::LOOP
{
    class BackgroundLoop : public virtual Loop
    {
    public:
        using Predicate = Loop::Predicate;
        using Callback = Loop::LoopCallback;


    private:
        PARALLEL::Worker<void> _bgThread;

    public:
        BackgroundLoop(Predicate const& predicate, Callback const& callback, PreCallback const& preCallback = [] { }, PostCallback const& postCallback = [] { });

        ~BackgroundLoop();

        void Run() final;

        /*!
         * Terminates the loop and joins the running thread.
         * This is equal to Terminate(true);
         */
        void Join();

        /*!
         * Terminates the loop. If the wait flag is set to false, termination does not wait for the background thread to finish.
         * @wait Wait for the thread to finish.
         */
        void Terminate(bool wait = true);


    private:
        /*!
         * Helper method to call the baseloop run method.
         */
        void TaskCallback();
    };
}
