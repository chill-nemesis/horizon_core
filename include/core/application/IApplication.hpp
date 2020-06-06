//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    21/02/2020 17:28
// @project Horizon
//


#pragma once

namespace HORIZON::CORE::APPLICATION
{
    class IApplication
    {
    public:
        inline virtual bool Initialise()
        { return true; }

        inline virtual void Destroy()
        { }

        inline virtual void Run()
        { }
    };
}