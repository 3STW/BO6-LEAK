#pragma once

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <random>

#include <dxgi1_4.h>
#include <sstream >

#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include <MinHook.h>
#pragma comment(lib, "minhook.lib")

#define QWORD unsigned __int64
#define Exit() 0

