#pragma once

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#define FMT_HEADER_ONLY
#define NOMINMAX
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_ENABLE_FREETYPE


#define SOL_ALL_SAFETIES_ON 1
#define SOL_DEFAULT_PASS_ON_ERROR  1
#define SOL_NO_CHECK_NUMBER_PRECISION 1

#include "sol/sol.hpp"

/// Common includes
#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <algorithm>
#include <cstdint>
#include <cctype>
#include <functional>
#include <thread>
#include <vector>
#include <array>
#include <map>
#include <deque>
#include <fstream>
#include <Psapi.h>
#include <sstream>
#include <libloaderapi.h>
#include <cmath>
#include <memory>
#include <stack>
#include <iostream>
#include <TlHelp32.h>
#include <any>
#include <array>
#include <filesystem>
#include <winternl.h>

/// Our stuff ( keep in alphabetical order )
#include "address/address.hpp"

#include "bitflag/bitflag.hpp"

#include "color/col_t.hpp"

#include "config/config.hpp"

#include "easing/easing.hpp"

#include "fmt/format.hpp"

//#include "gui/gui.hpp"

#include "hash/hash.hpp"

#include "hook/hook.hpp"

#include "input/input.hpp"

#include "json/json.hpp"

#include "libnop/libnop.hpp"

#include "log/log.hpp"

#include "math/math.hpp"

#include "mem/mem.hpp"

#include "mem_protect/mem_protect.hpp"

#include "misc/misc.hpp"

#include "profiler/profiler.hpp"

//#include "sol/sol.hpp"

#include "stack_frame/stack_frame.hpp"

#include "syscall/syscall.hpp"

#include "xorstr/xorstr.hpp"

#include "zydis/zydis.hpp"