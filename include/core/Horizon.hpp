//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    18/02/2020 13:24
// @project Horizon
//


#pragma once

#include "core/application/IApplication.hpp"
#include <module/ModuleLoader.hpp>
#include <log/Log.hpp>
#include <parallel/ThreadPool.hpp>
#include <time/Clock.hpp>
#include <arg/Args.hpp>
#include <ui/Window.hpp>

#include <memory>


extern std::unique_ptr<HORIZON::CORE::APPLICATION::IApplication> GetApp();


namespace HORIZON::CORE
{
    class Global
    {

        MakeStatic(Global);

    public:
        friend void Initialise(int& argc, char** argv);

        friend void Terminate();


    private:
        static std::shared_ptr<PARALLEL::ThreadPool> _pool;
        static std::shared_ptr<TIME::Clock>          _clock;


    public:
        /*!
         * The global thread pool.
         */
        static inline std::shared_ptr<PARALLEL::ThreadPool> const& ThreadPool()
        { return _pool; }

        /*!
         * The global timer.
         */
        static inline std::shared_ptr<TIME::Clock> const& Clock()
        { return _clock; }
    };
}