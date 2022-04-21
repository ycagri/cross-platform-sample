#pragma once

#include "LibBridge.g.h"

namespace winrt::lib::implementation
{
    struct LibBridge : LibBridgeT<LibBridge>
    {
        LibBridge() = default;

        winrt::hstring AddUser(const::winrt::hstring dbPath, const::winrt::hstring username);
        winrt::hstring GetUserRepos(const::winrt::hstring dbPath, const::winrt::hstring username);
    };
}

namespace winrt::lib::factory_implementation
{
    struct LibBridge : LibBridgeT<LibBridge, implementation::LibBridge>
    {
    };
}
