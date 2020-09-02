//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    28/03/2020 16:14
// @project Horizon
//


#pragma once

#include "core/application/IApplication.hpp"

#include <parallel/loop/Loop.hpp>
#include <callable/CallbackManager.hpp>
#include <algorithm/stl_extension/vector.hpp>


#include <functional>

namespace HORIZON::CORE::APPLICATION
{
    /*!
     * Runs a main loop (inside the main thread).
     * Callbacks are to be kept as fast as possible and must not block.
     * There is no guarantee of the execution order of callbacks.
     */
    template<class L,
            std::enable_if_t<std::is_base_of<PARALLEL::LOOP::Loop, L>::value, int> = 0>
    class BaseLoopApplication : public IApplication
    {
    public:
        using MainThreadCallback = std::function<void(void)>;
        using LoopType = L;
        using DeltaTime = typename LoopType::DeltaTime;

    private:
        std::shared_ptr<CALLABLE::CallbackManager<void(void)>> _mainThreadCallbacks;
        LoopType                                              _loop;


    public:
        BaseLoopApplication() :
                _mainThreadCallbacks(CALLABLE::CallbackManager<void(void)>::Create()),
                // first is loop terminate predicate, second is the loop callback for each tick
                _loop([] { return true; }, [this](DeltaTime) { _mainThreadCallbacks->Call(); })
        { }

        ~BaseLoopApplication()
        { Terminate(); }

        [[maybe_unused]] inline LoopType const& GetLoop() const
        { return _loop; }

        /*!
         * Terminates the running application.
         */
        inline void Terminate()
        { _loop.Terminate(); }

        /*!
         * Registers a callback for the main loop.
         * Each callback gets called once per loop cycle, but there is no guarantee on order.
         */
        inline CALLABLE::CallbackHandle Register(MainThreadCallback&& callback)
        { return std::move(_mainThreadCallbacks->Register(std::forward<MainThreadCallback>(callback))); }

        /*!
         * Starts user threads, then runs the main thread in a loop.
         */
        inline void Run() final
        {
            StartThreads();
            _loop.Run();
            StopThreads();
        }


    protected:
        /*!
         * Enables the inherited class to start threads (from the main thread), before it is blocked inside the application loop.
         */
        virtual void StartThreads()
        { }

        /*!
         * Enables the inherited class to stop/join threads with the main thread after Terminate has been called.
         */
        virtual void StopThreads()
        { }

    };
}