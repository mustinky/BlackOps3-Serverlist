#include "hook.h"

IDXGISwapChain* Hook::swap_chain = nullptr;
ID3D11Device* Hook::device = nullptr;
ID3D11DeviceContext* Hook::device_context = nullptr;
t_present Hook::original_present = nullptr;
t_resize_buffers Hook::original_resize_buffers = nullptr;
t_set_fullscreen_state Hook::original_set_fullscreen_state = nullptr;
HWND Hook::hwnd = nullptr;
HMODULE Hook::hmodule = nullptr;

int Hook::window_height = 0;
int Hook::window_width = 0;

void* Hook::swap_chain_table[40];
WNDPROC Hook::original_wndproc = nullptr;

void Hook::hook_directx()
{
    if (get_d3d11_swap_chain(swap_chain_table, sizeof(swap_chain_table)))
    {
        original_present = (t_present)swap_chain_table[8];
        original_resize_buffers = (t_resize_buffers)swap_chain_table[13];
        original_set_fullscreen_state = (t_set_fullscreen_state)swap_chain_table[10];

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)original_present, Drawing::hkPresent);
        DetourAttach(&(PVOID&)original_resize_buffers, hook_resize_buffers);
        DetourAttach(&(PVOID&)original_set_fullscreen_state, hook_set_fullscreen_state);
        DetourTransactionCommit();
    }
}

void Hook::unhook_directx()
{
    if (Drawing::bInit)
    {
        unhook_window();
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        device_context->Release();
        device->Release();
    }

    Drawing::bInit = false;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)original_present, Drawing::hkPresent);
    DetourDetach(&(PVOID&)original_resize_buffers, hook_resize_buffers);
    DetourDetach(&(PVOID&)original_set_fullscreen_state, hook_set_fullscreen_state);
    DetourTransactionCommit();
}

HWND Hook::get_process_window()
{
    hwnd = nullptr;

    EnumWindows(enum_windows, NULL);

    RECT size;
    if (hwnd == nullptr)
        return nullptr;

    GetWindowRect(hwnd, &size);

    window_width = size.right - size.left;
    window_height = size.bottom - size.top;

    window_height -= 29;
    window_width -= 5;

    return hwnd;
}

BOOL Hook::get_d3d11_swap_chain(void** p_table, const size_t size)
{
    if (!p_table)
        return FALSE;

    ID3D11Device* pd3d_device = nullptr;
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = get_process_window();
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swap_chain, &pd3d_device, nullptr, nullptr);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swap_chain, &pd3d_device, nullptr, nullptr);

    if (res != S_OK)
        return false;

    memcpy(p_table, *(void***)(swap_chain), size);

    swap_chain->Release();
    pd3d_device->Release();

    return TRUE;
}

void Hook::hook_window()
{
    original_wndproc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)wnd_proc);
}

void Hook::unhook_window()
{
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)original_wndproc);
}

LRESULT WINAPI Hook::wnd_proc(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
    if (Drawing::bDisplay && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        ImGui::GetIO().MouseDrawCursor = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
        return true;
    }

    if (Drawing::bInit)
        ImGui::GetIO().MouseDrawCursor = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);

    if (msg == WM_CLOSE)
    {
        unhook_directx();
        unhook_window();
        TerminateProcess(GetCurrentProcess(), 0);
    }

    return CallWindowProc(original_wndproc, hWnd, msg, wParam, lParam);
}

HRESULT Hook::hook_resize_buffers(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    unhook_window();

    if (Drawing::bInit)
    {
        Drawing::bInit = false;
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        device_context->Release();
        device->Release();
    }

    swap_chain = nullptr;
    device = nullptr;
    device_context = nullptr;

    return original_resize_buffers(pThis, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT Hook::hook_set_fullscreen_state(IDXGISwapChain* pThis, BOOL FullScreen, IDXGIOutput* pTarget)
{
    unhook_window();

    if (Drawing::bInit)
    {
        Drawing::bInit = false;
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        device_context->Release();
        device->Release();
    }

    swap_chain = nullptr;
    device = nullptr;
    device_context = nullptr;

    return original_set_fullscreen_state(pThis, FullScreen, pTarget);
}

BOOL CALLBACK Hook::enum_windows(HWND handle, LPARAM lp)
{
    DWORD proc_id;

    GetWindowThreadProcessId(handle, &proc_id);

    if (GetCurrentProcessId() != proc_id)
        return TRUE;

    hwnd = handle;
    return FALSE;
}
