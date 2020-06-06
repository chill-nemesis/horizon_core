//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon_2@ch3ll.com
// @version 1.0.0
// @date    24/12/2019 16:57
// @project Horizon
//


#pragma once

namespace HORIZON::CORE
{
    /*!
     * Starts the engine.
     */
    void Initialise(int argc, char** argv);


    /*!
     * Runs the user application.
     */
    void RunApplication();

    /*!
     * Terminates the engine.
     */
    void Terminate();
}