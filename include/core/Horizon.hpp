//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    18/02/2020 13:24
// @project Horizon
//


#pragma once

#include "core/application/IApplication.hpp"
#include <log/Log.hpp>
#include <memory>


extern std::unique_ptr<HORIZON::CORE::APPLICATION::IApplication> GetApp();
