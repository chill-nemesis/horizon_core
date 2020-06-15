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
#include <ui/UIModule.hpp>
#include <opengl/OpenGLModule.hpp>
#include <opengl/OpenGL.hpp>

using namespace HORIZON::CORE::APPLICATION;
using namespace HORIZON::CORE::LOOP;
using namespace HORIZON::UI;
using namespace HORIZON::OPENGL;
using namespace HORIZON::PARALLEL;


GameApplication::GameApplication() :
        _window(),
        _updateLoop([] { return true; }, [this](DeltaTime const& time) { Update(time); }),
        _renderLoop([] { return true; }, [this](DeltaTime const& time) { Render(time); },
                    [this]() { PreRender(); }, [this]() { PostRender(); })
{ }

GameApplication::~GameApplication()
{
    Destroy();
}

bool GameApplication::Initialise()
{
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
    _window->Close();
}

void GameApplication::Update(const DeltaTime& time)
{
    // update input for next frame
    _window->GetInput().Next();
}

void GameApplication::PreRender() noexcept
{
    // TODO: move that to a render queue?
    GetWindow()->MakeContextCurrent();
    glClearColor(0, 0, 0, 1);
    glViewport(0, 0, 640, 480);

}

void GameApplication::Render(const DeltaTime& time)
{
    //TODO: renderer draw

    _window->SwapBuffers();
}

void GameApplication::PostRender() noexcept
{
    // make sure that all gpu memory is freed
}

void GameApplication::OnWindowClosed(Window const& window)
{
    //TODO: detect window replacement


    // join threads !BEFORE! signaling main thread, otherwise we might have (access) race conditions.
    _updateLoop.Join();
    _renderLoop.Join();

    // signal main thread loop to stop
    Terminate();
}