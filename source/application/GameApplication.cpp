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
#include <module/ModuleLoader.hpp>
#include <ui/UIModule.hpp>
#include <opengl/OpenGLModule.hpp>
#include <opengl/OpenGL.hpp>

using namespace HORIZON::CORE::APPLICATION;
using namespace HORIZON::CORE::LOOP;
using namespace HORIZON::MODULE;
using namespace HORIZON::UI;
using namespace HORIZON::OPENGL;
using namespace HORIZON::PARALLEL;


GameApplication::GameApplication() :
        _window(),
        _updateLoop([this] { return HasWindow(); }, [this](DeltaTime const& time) { InternalUpdate(time); }),
        _renderLoop([this] { return HasWindow(); }, [this](DeltaTime const& time) { InternalRender(time); }, [this]
        {
            GetWindow()->MakeContextCurrent();      // TODO: move that to a render queue?
            glClearColor(0, 0, 0, 1);
            glViewport(0, 0, 640, 480);
        })
{ }

GameApplication::~GameApplication()
{
    Destroy();
}

bool GameApplication::Initialise()
{
    // Load additional modules
    if (!(ModuleLoader::Load(UI::GetModule()) && ModuleLoader::Load(OPENGL::GetModule())))
        return false;

    SetWindow<UI::Window>(GetStartupWindowSettings());

    // register the event polling to the main loop
    // this blocks the main thread because no timeout is specified!
    Register([] { return UI::WaitEvents(); });

    // make sure to give up context here, otherwise i cannot move it to the render thread!
    Window::FreeContext();

    return true;
}


void GameApplication::StartThreads()
{
    _updateLoop.Run();
    _renderLoop.Run();
}


void GameApplication::Destroy()
{
    // Close window if this was called from outside
    // This also stops the loops for update and render.
    if (_window) _window->Close();
}

void GameApplication::InternalUpdate(const DeltaTime& time)
{
    // update input for next frame
    _window->GetInput()->Next();

    Update(time);
}

void GameApplication::InternalRender(const DeltaTime& time)
{
    Render(time);

    _window->SwapBuffers();
}

void GameApplication::OnWindowClosed(std::shared_ptr<UI::Window> const& window)
{
    // only release the smart pointer if they point to the same window, otherwise it is a replacement
    if (window == _window)
    {
        // signal main thread loop to stop
        Terminate();

        // join threads !BEFORE! signaling main thread, otherwise we might have (access) race conditions.
        _updateLoop.Join();
        _renderLoop.Join();

        // release "our" pointer of the window
        // window destruction can start from here (normally, it should only happen after this method returns, see WindowManager).
        _window.reset();
    }
}