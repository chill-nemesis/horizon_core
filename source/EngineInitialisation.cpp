//
// @brief
// @details
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    24/12/2019 17:10
// @project Horizon
//

#define STRING(s)        #s
#define EXPAND_STRING(s) STRING(s)


#include "core/EngineInitialisation.hpp"

#include "core/Horizon.hpp"

#include <arg/Args.hpp>
#include <chrono>
#include <csignal>
#include <format>
#include <log/Log.hpp>
#include <log/LogModule.hpp>
#include <mutex>
#include <opengl/OpenGLModule.hpp>
#include <parallel/async/Async.hpp>
#include <ui/UIModule.hpp>


using namespace HORIZON::LOG;


bool       _engineInitialised = false;
std::mutex _entryGuard;

namespace HORIZON::CORE
{
	void TerminateEngine(int signal)
	{
		Warn("Received termination signal ", signal, ".");

		// TODO: stop running app

		// try to access the lock (this serves as a check whether the crash occurred during init/destroy
		if (_entryGuard.try_lock())
		{
			_entryGuard.unlock();
			Terminate();

			// this tries to clean up resources
			exit(signal);
		}
		else
		{
			Error("Error occurred during initialisation or termination. No graceful shutdown possible!");

			// this is the nuke...
			abort();
		}
	}

	void AddSystemSignals()
	{
		signal(SIGINT, TerminateEngine);
		// do not register abort signal, this is the nuke option
		//  signal(SIGABRT, TerminateEngine);
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
			Warn("Engine already running, ignoring additional call to initialise!");
			return;
		}


		// Add system signals
		AddSystemSignals();

		Info("Starting Horizon.");
#if HORIZON_DEBUG_BUILD
		Warn("Running DEBUG build!");
#endif

		// Print info:
		{
			auto now = std::chrono::system_clock::now();
			Info("Current date-time is ", std::format("{:%F %T}", now));
			Info("Compiled for: ", HORIZON_OS_NAME, " v.", EXPAND_STRING(HORIZON_OS_VERSION));
		}


		// Load modules
		{
			using namespace HORIZON::ARG;
			using namespace HORIZON::LOG;
			using namespace HORIZON::PARALLEL::ASYNC;
			using namespace HORIZON::TIME;

			Info("Loading core modules: ");

			// Parse arguments
			ParseArgs(argc, argv);

			// make the global thread pool
			// thread pool does not require log module
			SetGlobalThreadPool(std::make_shared<ThreadPool>());

			// TODO: make that nicer, order is important!
			if (!(LOG::Initialise() && UI::Initialise() && OPENGL::Initialise()))
			{
				Error("Error starting core modules, terminating Horizon.");
				lock.unlock();
				Terminate();
				return;
			}
		}

		Info("Core successfully initialised.");


		_engineInitialised = true;
	}

	void Terminate()
	{
		std::unique_lock<std::mutex> lock(_entryGuard);

		if (!_engineInitialised) { Warn("Engine is not initialised. Trying to terminate..."); }


		Info("Initiating shutdown");

		LOG::Destroy();

		PARALLEL::ASYNC::ReleaseGlobalThreadPool();

		_engineInitialised = false;
	}

}  // namespace HORIZON::CORE