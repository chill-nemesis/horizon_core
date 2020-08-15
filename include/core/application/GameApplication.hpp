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
#include <render/RenderManager.hpp>

#include <memory>


namespace HORIZON::CORE::APPLICATION
{
    class GameApplication : public BaseLoopApplication<PARALLEL::LOOP::Loop>
    {
    private:
        UI::Window            _window;
        RENDER::RenderManager _renderManager;


    public:
        explicit GameApplication(UI::WindowSettings const& settings = UI::WindowSettings());

        ~GameApplication();

        bool Initialise() final;


        void Destroy() final;

        [[nodiscard]] inline UI::Window& GetWindow()
        { return _window; }

        inline RENDER::SCENE::SceneManager& GetSceneManager() noexcept
        { return _renderManager.GetSceneManager(); }

        //    TODO: window replacement/settings change?

    protected:
        void StartThreads() final;
    };
}