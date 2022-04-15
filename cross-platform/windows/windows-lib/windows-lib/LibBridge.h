#pragma once

#include "LibBridge.g.h"

namespace winrt::windows_lib::implementation
{
    struct LibBridge : LibBridgeT<LibBridge>
    {
        LibBridge() = default;

        winrt::hstring AddUser(const::winrt::hstring dbPath, const::winrt::hstring username);
        winrt::hstring GetUserRepos(const::winrt::hstring dbPath, const::winrt::hstring username);
    };
}

namespace winrt::windows_lib::factory_implementation
{
    struct LibBridge : LibBridgeT<LibBridge, implementation::LibBridge>
    {
    };
}
