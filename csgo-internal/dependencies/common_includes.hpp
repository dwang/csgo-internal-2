#pragma once

#define VC_EXTRALEAN
#include <Windows.h>
#include <iostream>
#include <thread>
#include <cstdint>
#include <memory>

#include "utilities/singleton.hpp"
#include "utilities/vmt.hpp"
#include "utilities/utilities.hpp"
#include "utilities/fnv.hpp"
#include "utilities/netvars.hpp"

#include "interfaces/interfaces.hpp"

#include "../core/features/features.hpp"
#include "../sdk/sdk.hpp"
#include "../core/hooks/hooks.hpp"
