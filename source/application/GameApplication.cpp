//
// @brief
// @details
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    11/03/2020 17:17
// @project Horizon
//

#include "core/application/GameApplication.hpp"

#include <opengl/OpenGL.hpp>
#include <opengl/OpenGLModule.hpp>
#include <ui/UIModule.hpp>

using namespace HORIZON::CORE::APPLICATION;
using namespace HORIZON::PARALLEL::LOOP;
using namespace HORIZON::UI;
using namespace HORIZON::OPENGL;
using namespace HORIZON::PARALLEL;

GameApplication::GameApplication(WindowSettings const& settings) :
	_window(settings),  // this order matters (render manager releases UI from thread; render manager needs the correct
						// window instance)
	_renderManager(_window)
{
	// render manager self-manages loop-termination, so there is no need to register NotifyOnClose for rendermanager
	// here

	// TODO: detect window replacement
	// register window closing to notify the game app. This terminates the app.
	_events.emplace_back(_window.NotifyOnClose([this](Window const&) { Terminate(); }));
}

GameApplication::~GameApplication() { Destroy(); }

bool GameApplication::Initialise()
{
	// register the event polling to the main loop
	// this blocks the main thread because no timeout is specified!
	_events.emplace_back(Register([] { return UI::WaitEvents(); }));

	return true;
}

void GameApplication::StartThreads() { _renderManager.Start(); }

// Stop threads is not necessary, since rendermanager stops itself once the window is getting closed.

void GameApplication::Destroy() noexcept
{
	// Close window if this was called from outside
	// This also stops the loops for update and render.
	_window.Close();
}