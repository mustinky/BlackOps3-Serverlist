#include "Core/hook/hook.h"

inline PVOID hook_vtable_function(_In_ ULONG_PTR* vtable, _In_ LPVOID detour, _In_opt_ SIZE_T table_index)
{
    static DWORD old_protect = NULL;

    if (!VirtualProtect(&vtable[table_index], sizeof(ULONG_PTR), PAGE_READWRITE, &old_protect))
        return nullptr;

    LPVOID original_function = (LPVOID)(vtable[table_index]);
    vtable[table_index] = (ULONG_PTR)(detour);
    VirtualProtect(&vtable[table_index], sizeof(ULONG_PTR), old_protect, &old_protect);

    return original_function;
}

inline __int64 __fastcall dlc_hook(__int64 a1, __int64 a2)
{
    if (a1 == 366843 || a2 == 366841)
        return true;

    switch (a2) {
    case 830450:
    case 830451:
    case 830460:
    case 830461:
    case 624760:
    case 460110:
    case 648460:
    case 437351:
    case 437350:
        return false;
    default:
        return true;
    }
}

inline void spoof_dlc()
{
    static bool is_hooked = false;

    if (!is_hooked)
    {
        ULONG64* dlc_vtable = **(ULONG64***)(Engine::offset(0xCE16752F));
        hook_vtable_function(dlc_vtable, &dlc_hook, 7);

        is_hooked = true;
    }
}

BOOL WINAPI DllMain(const HINSTANCE hinst_dll, const DWORD fdw_reason, LPVOID lp_reserved)
{
    switch (fdw_reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinst_dll);
        Hook::hmodule = hinst_dll;
        spoof_dlc();
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Hook::hook_directx, nullptr, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        Hook::unhook_directx();
        break;
    }

    return TRUE;
}
