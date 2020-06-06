//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    24/12/2019 17:10
// @project Horizon
//

#define STRING(s) #s
#define EXPAND_STRING(s) STRING(s)


#include "core/EngineInitialisation.hpp"
#include "core/Horizon.hpp"


#include <log/LogModule.hpp>
#include <ui/UIModule.hpp>
#include <opengl/OpenGLModule.hpp>
#include <arg/Args.hpp>
#include <csignal>

using namespace HORIZON::LOG;
using namespace HORIZON::MODULE;


bool       _engineInitialised = false;
std::mutex _entryGuard;

namespace HORIZON::CORE
{
    void TerminateEngine(int signal)
    {
        Warn("Received termination signal ", signal, ".");

        //TODO: stop running app

        Terminate();

        exit(signal);
    }

    void AddSystemSignals()
    {
        signal(SIGINT, TerminateEngine);
        signal(SIGABRT, TerminateEngine);
        signal(SIGTERM, TerminateEngine);
        #if _POSIX
        signal(SIGKILL, TerminateEngine);
        #endif
    }


    void Initialise(int argc, char** argv)
    {
        std::unique_lock<std::mutex> lock(_entryGuard);

        if (_engineInitialised)
        {
            Debug("Engine already running, ignoring further calls to initialise.");
            return;
        }




        // Add system signals
        AddSystemSignals();


        Info("Starting Horizon.");
        #if HORIZON_DEBUG_BUILD
        Warn("Running DEBUG build!");
        #endif



        // Load modules
        {
            using namespace HORIZON::ARG;
            using namespace HORIZON::LOG;
            using namespace HORIZON::PARALLEL;
            using namespace HORIZON::TIME;

            Info("Loading core modules: ");

            // Parse arguments
            ParseArgs(argc, argv);


            //TODO: make that nicer
            if (!(ModuleLoader::Load(LOG::GetModule())))
            {
                Error("Error starting core modules, terminating Horizon.");
                lock.unlock();
                Terminate();
                return;
            }
        }


        Info("Compiled for: ", HORIZON_OS_NAME, " v.", EXPAND_STRING(HORIZON_OS_VERSION));
        Info("Core successfully initialised.");


        _engineInitialised = true;
    }

    void Terminate()
    {
        std::unique_lock<std::mutex> lock(_entryGuard);

        if (!_engineInitialised)
        {
            Warn("Engine is not initialised, ignoring call to terminate.");
            return;
        }


        Info("Initiating shutdown");


        ModuleLoader::Unload();

        _engineInitialised = false;
    }

}