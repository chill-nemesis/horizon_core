//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    30/01/2020 22:13
// @project Horizon
//


#include "core/Horizon.hpp"
#include "core/EngineInitialisation.hpp"
#include <iostream>

using namespace HORIZON::CORE;

int main(int argc, char** argv)
{
    Initialise(argc, argv);

    try
    {
        RunApplication();
    } catch (std::exception& e)
    {
        //TODO: move that into engine code?
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    Terminate();


    return 0;
}