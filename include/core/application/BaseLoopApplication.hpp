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

#include "IApplication.hpp"
#include "../loop/Loop.hpp"
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
            std::enable_if_t<std::is_base_of<LOOP::Loop, L>::value, int> = 0>
    class BaseLoopApplication : public IApplication
    {
    public:
        using LoopCallback = std::function<void(void)>;
        using LoopType = L;

    private:
        using LoopCallbackContainer = std::vector<LoopCallback>;


        LoopCallbackContainer _callbacks;
        LoopType              _loop;


    public:
        BaseLoopApplication() :
                _loop([] { return true; }, std::bind(&BaseLoopApplication<L>::LoopTick, this))
        { }

        ~BaseLoopApplication()
        {
            Terminate();
        }

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
        inline void Register(LoopCallback const& callback)
        { _callbacks.push_back(callback); }

        /*!
         * Tries to remove a previously added callback.
         * @return True if successful, false otherwise.
         */
        [[maybe_unused]] inline bool Unregister(LoopCallback const& callback)
        { return ALGORITHM::STL_EXTENSION::EraseItemFromVector(_callbacks, callback); }

        /*!
         * Starts user threads, then runs the main thread in a loop.
         */
        inline void Run() final
        {
            StartThreads();
            _loop.Run();
        }


    protected:
        /*!
         * Enables the inherited class to start threads (from the main thread), before it is blocked inside the application loop.
         */
        virtual void StartThreads()
        { }

    private:
        /*!
         * The callback for each loop tick
         */
        void LoopTick()
        {
            for (auto& callback : _callbacks)
                callback();
        }

    };
}