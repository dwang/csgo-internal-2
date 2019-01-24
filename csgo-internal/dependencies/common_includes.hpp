#pragma once

#define VC_EXTRALEAN
#include <Windows.h>
#include <iostream>
#include <thread>
#include <cstdint>
#include <memory>
#include <array>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/examples/imgui_impl_dx9.h"
#include "imgui/examples/imgui_impl_win32.h"

#include "utilities/singleton.hpp"
#include "utilities/globals.hpp"
#include "utilities/hotkeys.hpp"
#include "utilities/vmt.hpp"
#include "utilities/render.hpp"
#include "utilities/utilities.hpp"
#include "utilities/fnv.hpp"
#include "utilities/netvars.hpp"

#include "interfaces/interfaces.hpp"

#include "../core/features/features.hpp"
#include "../core/menu/menu.hpp"
#include "../sdk/sdk.hpp"
#include "../core/hooks/hooks.hpp"
