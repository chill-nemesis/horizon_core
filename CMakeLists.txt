cmake_minimum_required(VERSION 3.15)
project(horizon VERSION 0.0.0 LANGUAGES CXX C)

include(HorizonCommon)

include_directories(include/)


set(HEADER
        include/core/EngineInitialisation.hpp
        include/core/Horizon.hpp
        include/core/application/IApplication.hpp
        include/core/application/GameApplication.hpp
        include/core/loop/Loop.hpp
        include/core/loop/Loop.hpp
        include/core/loop/FixTickLoop.hpp
        include/core/loop/BackgroundLoop.hpp
        include/core/application/BaseLoopApplication.hpp
        include/core/loop/BackgroundLoop.hpp
        include/core/loop/BackgroundFixTickLoop.hpp)

set(SOURCE
        source/EngineInitialisation.cpp
        source/main.cpp
        source/EngineRun.cpp
        source/application/GameApplication.cpp
        source/loop/Loop.cpp
        source/loop/BackgroundLoop.cpp)

set(HORIZON_COMPILE_SOURCES ${HEADER} ${SOURCE})


add_library(horizon ${HORIZON_COMPILE_SOURCES})
# TODO: fix required modules
target_link_libraries(horizon horizon_parallel horizon_log horizon_time horizon_parallel horizon_ui horizon_opengl horizon_arg)

target_include_directories(horizon PUBLIC include/)