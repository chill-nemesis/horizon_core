//
// @brief
// @details
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    28/02/2020 19:54
// @project Horizon
//

#include "horizon/core/EngineInitialisation.hpp"
#include "horizon/core/Horizon.hpp"
#include "horizon/core/application/IApplication.hpp"

#include <horizon/arg/Args.hpp>
#include <horizon/log/Log.hpp>

using namespace HORIZON;
using namespace HORIZON::CORE::APPLICATION;
using namespace HORIZON::PARALLEL;
using namespace HORIZON::TIME;
using namespace HORIZON::LOG;

void HORIZON::CORE::RunApplication()
{
	Debug("Running application ", ARG::GetAppPath(), ".");

	auto app = GetApp();

	if (!app->Initialise())
	{
		Warn("Error initialising application.");
		app->Destroy();
		return;
	}

	app->Run();

	app->Destroy();
}