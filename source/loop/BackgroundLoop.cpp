//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   Horizon@ch3ll.com
// @version 1.0.0
// @date    30/03/2020 16:42
// @project Horizon
//

#include "core/loop/BackgroundLoop.hpp"

#include <utility>

using namespace HORIZON::CORE::LOOP;
using namespace HORIZON::PARALLEL;

BackgroundLoop::BackgroundLoop(Predicate const& predicate, Callback const& callback, PreCallback const& preCallback, PostCallback const& postCallback) :
        Loop(predicate, callback, preCallback, postCallback),
        _bgThread(make_worker([this] { TaskCallback(); }))
{ }

BackgroundLoop::~BackgroundLoop()
{
    Join();
}

void BackgroundLoop::Run()
{
    //problem: because Run is overwritten (duh), the worker will also call this run instead of the expected BaseLoop::Run
    _bgThread.Start();
}

void BackgroundLoop::TaskCallback()
{ Loop::Run(); }

void BackgroundLoop::Join()
{ Terminate(true); }

void BackgroundLoop::Terminate(bool wait)
{
    Loop::Terminate();

    // wait for the background thread to join.
    if (wait) _bgThread.Join();
}