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

#include "core/application/BaseLoopApplication.hpp"
#include "core/loop/BackgroundFixTickLoop.hpp"
#include "core/loop/BackgroundLoop.hpp"
#include <ui/Window.hpp>
#include <time/Clock.hpp>
#include <memory>


namespace HORIZON::CORE::APPLICATION
{
    class GameApplication : public BaseLoopApplication<LOOP::Loop>
    {
        //    TODO: maybe have a threadpool per application instance?

    public:
        using DeltaTime = TIME::Clock::DurationType;
        using UpdateLoop = LOOP::BackgroundFixTickLoop<60>;

    private:
        std::shared_ptr<UI::Window> _window;
        UpdateLoop                  _updateLoop;
        LOOP::BackgroundLoop        _renderLoop;


    public:
        GameApplication();

        ~GameApplication();

        bool Initialise() final;


        void Destroy() final;

        [[nodiscard]] inline std::shared_ptr<UI::Window> const& GetWindow() const
        { return _window; }

        [[nodiscard]]inline bool HasWindow() const
        { return static_cast<bool>(_window); }

        template<typename R>
        std::enable_if_t<std::is_base_of<UI::Window, R>::value, void>
        SetWindow(UI::WindowSettings const& settings)
        {
            //TODO: what if window needs to be replaced?

            std::shared_ptr<UI::Window> window = UI::make_window<R>(settings);
            window->NotifyOnClose([this](std::shared_ptr<UI::Window> const& window) { OnWindowClosed(window); });
            // this swaps the handled pointer from the previous window to the newly created one for all holders of the shared_ptr
            _window.swap(window);

            // window now contains the old window and will be released when out of scope. This triggers the destruction (and close call)
        }

        /*!
         * Pass-through for window events.
         */
        [[nodiscard]] std::shared_ptr<UI::INPUT::InputHandler> const& Events() const
        {
            return _window->GetInput();
        }


    protected:
        [[nodiscard]] virtual UI::WindowSettings GetStartupWindowSettings() const = 0;


        virtual void Update(DeltaTime time) = 0;

        virtual void Render(DeltaTime time) = 0;

        void StartThreads() final;

    private:

        void InternalUpdate(DeltaTime const& time);

        void InternalRender(DeltaTime const& time);

        void OnWindowClosed(std::shared_ptr<UI::Window> const& window);
    };
}