cmake_minimum_required(VERSION 3.15)
project(horizon VERSION 0.0.0 LANGUAGES CXX C)

set(HEADER
        include/core/EngineInitialisation.hpp
        include/core/Horizon.hpp
        include/core/application/IApplication.hpp
        include/core/application/GameApplication.hpp
        include/core/application/BaseLoopApplication.hpp)

set(SOURCE
        source/EngineInitialisation.cpp
        source/main.cpp
        source/EngineRun.cpp
        source/application/GameApplication.cpp)

# TODO: fix required modules
MakeHorizonModule(
        COMPILE_SOURCE ${HEADER} ${SOURCE}
        PUBLIC_DEPENDENCIES horizon_parallel horizon_log horizon_time horizon_parallel horizon_ui horizon_opengl horizon_arg horizon_render horizon_callable
)