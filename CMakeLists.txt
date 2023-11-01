cmake_minimum_required(VERSION 3.15)
project(horizon_core VERSION 0.0.0 LANGUAGES CXX C)

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
        COMPILE_SOURCE ${HEADER} ${SOURCE}
        # TODO: fix required modules!
        PUBLIC_DEPENDENCIES horizon::arg horizon::log horizon::algorithm horizon::callable horizon::parallel horizon::render horizon::ui
        COMPILE_DEFINITIONS ${COMPILE_DEFINITIONS}
)
