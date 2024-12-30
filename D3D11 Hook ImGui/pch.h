#ifndef PCH_H
#define PCH_H

#include <Windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include "detours.h"
#include "d3d11.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "ntdll.lib")

#include "Core/engine/engine.hpp"
#include "Core/hook/hook.h"
#include "Core/ui/drawing.h"
#include "Core/ui/serverlist/servers.h"

#endif //PCH_H
