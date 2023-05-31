cmake_minimum_required(VERSION 3.15)
project(horizon VERSION 0.0.0 LANGUAGES CXX C)

include(HorizonCommon)

set(HEADER
        include/core/EngineInitialisation.hpp
        include/core/Horizon.hpp
        include/core/application/IApplication.hpp
        include/core/application/GameApplication.hpp
        include/core/application/BaseLoopApplication.hpp)

set(SOURCE
        source/application/GameApplication.cpp
        source/EngineInitialisation.cpp
        source/EngineRun.cpp
        source/main.cpp)

MakeHorizonModule(
        MODULE_NAME horizon
        COMPILE_SOURCE ${HEADER} ${SOURCE}
        # TODO: fix required modules!
        PUBLIC_DEPENDENCIES horizon_arg horizon_log horizon_algorithm horizon_callable horizon_parallel horizon_render horizon_ui
        COMPILE_DEFINITIONS ${COMPILE_DEFINITIONS}
)
