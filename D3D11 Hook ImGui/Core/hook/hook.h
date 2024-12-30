
#ifndef HOOK_H
#define HOOK_H

#include "../../pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using t_present = HRESULT(APIENTRY*)(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flag);
using t_resize_buffers = HRESULT(APIENTRY*)(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
using t_set_fullscreen_state = HRESULT(APIENTRY*)(IDXGISwapChain* pThis, BOOL FullScreen, IDXGIOutput* pTarget);

class Hook
{
public:

    static IDXGISwapChain* swap_chain;
    static ID3D11Device* device;
    static ID3D11DeviceContext* device_context;
    static t_present original_present;
    static t_resize_buffers original_resize_buffers;
    static t_set_fullscreen_state original_set_fullscreen_state;
    static HWND hwnd;
    static HMODULE hmodule;

    static void hook_directx();
    static void unhook_directx();
    static void hook_window();
    static void unhook_window();

private:
    static int window_height, window_width;
    static void* swap_chain_table[40];
    static WNDPROC original_wndproc;

    static BOOL CALLBACK enum_windows(HWND handle, LPARAM lp);
    static HWND get_process_window();
    static BOOL get_d3d11_swap_chain(void** p_table, size_t size);
    static LRESULT WINAPI wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static HRESULT APIENTRY hook_resize_buffers(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
    static HRESULT APIENTRY hook_set_fullscreen_state(IDXGISwapChain* pThis, BOOL FullScreen, IDXGIOutput* pTarget);
};

#endif 
