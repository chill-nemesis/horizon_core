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

#include <ui/Window.hpp>
#include <callable/CallbackManager.hpp>
#include <render/RenderManager.hpp>

#include <memory>


namespace HORIZON::CORE::APPLICATION
{
    /*!
     * @details The application interface for games. This class provides ui-management and a render manager.
     */
    class GameApplication : public BaseLoopApplication<PARALLEL::LOOP::Loop>
    {
    private:
        UI::Window                            _window;
        RENDER::RenderManager                 _renderManager;
        std::vector<CALLABLE::CallbackHandle> _events;


    public:
        /*!
         * @brief Creates a new game application.
         * @param settings  The window settings used during UI creation.
         */
        explicit GameApplication(UI::WindowSettings const& settings = UI::WindowSettings());

        /*!
         * @details Makes sure that all ui and render elements attached to this application are freed.
         */
        ~GameApplication();

        /*!
         * @details Attaches the game application callbacks to the loop tick.
         * @return  True if the application could be initialised successfully.
         */
        bool Initialise() final;

        /*!
         * @details Makes sure that all attached elements (ui and render components) are released. After calling this method, the application will
         * be in a valid state but cannot do anything besides terminating.
         */
        void Destroy() final;

        /*!
         * @details After a call to Destroy() the window will be closed.
         * @return The associated window.
         */
        [[nodiscard]] inline UI::Window& GetWindow()
        { return _window; }

        /*!
         * @return The scene manager of the application.
         */
        inline RENDER::SCENE::SceneManager& GetSceneManager() noexcept
        { return _renderManager.GetSceneManager(); }

        //    TODO: window replacement/settings change?

    protected:
        void StartThreads() final;
    };
}