//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    11/03/2020 16:47
// @project Horizon
//


#pragma once

#include <memory>

#include <ui/Window.hpp>
#include <time/Clock.hpp>
#include <render/scene/SceneManager.hpp>

#include "core/application/BaseLoopApplication.hpp"
#include "core/loop/BackgroundFixTickLoop.hpp"
#include "core/loop/BackgroundLoop.hpp"


namespace HORIZON::CORE::APPLICATION
{
    class GameApplication : public BaseLoopApplication<LOOP::Loop>
    {
        //    TODO: maybe have a threadpool per application instance?

    public:
        using DeltaTime = TIME::Clock::DurationType;
        using UpdateLoop = LOOP::BackgroundFixTickLoop<60>;

    private:
        std::shared_ptr<UI::Window> _window = nullptr;
        UpdateLoop                  _updateLoop;
        LOOP::BackgroundLoop        _renderLoop;


    public:
        GameApplication();

        ~GameApplication();

        bool Initialise() final;


        void Destroy() final;

        [[nodiscard]] inline std::shared_ptr<UI::Window>& GetWindow()
        { return _window; }

        template<typename R>
        std::enable_if_t<std::is_base_of<UI::Window, R>::value, void>
        SetWindow(UI::WindowSettings const& settings)
        {
            //TODO: what if window needs to be replaced?

            auto newWindow = std::make_shared<R>(settings);
            newWindow->NotifyOnClose([this](UI::Window const& window) { OnWindowClosed(window); });

            // this triggers the destructor of the old window
            _window.swap(newWindow);
        }


    protected:
        [[nodiscard]] virtual UI::WindowSettings GetStartupWindowSettings() const = 0;

        void StartThreads() final;

    private:

        void PreRender() noexcept;

        void PostRender() noexcept;

        void Update(DeltaTime const& time);

        void Render(DeltaTime const& time);

        void OnWindowClosed(UI::Window const& window);
    };
}