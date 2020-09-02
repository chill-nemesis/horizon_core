cmake_minimum_required(VERSION 3.15)
project(horizon VERSION 0.0.0 LANGUAGES CXX C)

include(HorizonCommon)

include_directories(include/)


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

set(HORIZON_COMPILE_SOURCES ${HEADER} ${SOURCE})


add_library(horizon ${HORIZON_COMPILE_SOURCES})
# TODO: fix required modules
target_link_libraries(horizon horizon_parallel horizon_log horizon_time horizon_parallel horizon_ui horizon_opengl horizon_arg horizon_render horizon_callable)

target_include_directories(horizon PUBLIC include/)


# TODO: quick fix to propagate the _USE_MATH_DEFINES flag to the target
if (${MSVC})
    target_compile_definitions(horizon PUBLIC _USE_MATH_DEFINES)
endif ()