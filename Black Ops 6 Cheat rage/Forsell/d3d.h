#pragma once

extern HWND wndproc;
extern void PreDraw2D(__int64 a1/*, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6, unsigned int a7*/);
inline uintptr_t vtable_original;
inline uintptr_t R_EndFrame_original;
extern void EnableHandler(void);
extern void R_EndFrame_hook();
inline uintptr_t packet_hook_orginal;
extern char  packet_test_hook(int a1, unsigned int a2);
inline uintptr_t CG_ViewMP_DrawActiveFrame_orginal;
extern uintptr_t CG_ViewMP_DrawActiveFrame_hook(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, char a6, unsigned int a7);
namespace D3D12 {

    enum class Status {
        UnknownError = -1,
        NotSupportedError = -2,
        ModuleNotFoundError = -3,

        AlreadyInitializedError = -4,
        NotInitializedError = -5,

        Success = 0,
    };

    Status Initd3d12();
    extern bool CreateDeviceD3D();
    extern void DrawCB(const std::function<void(void)>& callback);
    Status InstallHooks();
    Status RemoveHooks();
}



















