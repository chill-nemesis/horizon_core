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
    /*!
     * @brief Minimal interface for a horizon-application.
     * @sa GetApp()
     */
    class IApplication
    {
    public:
        /*!
         * @deatils Initialisation occurs before the application is run.
         * This method mainly exists to provide a safe way of calling possibly inherited code (from further down the inheritance tree).
         * @return  True if the initialisation is successful.
         */
        inline virtual bool Initialise()
        { return true; }

        /*!
         * @details Destroys the application.
         * This method is called after run completes.
         */
        inline virtual void Destroy() noexcept
        { }

        /*!
         * @brief Runs the application.
         */
        inline virtual void Run()
        { }
    };
}