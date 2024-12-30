#include "Drawing.h"

BOOL Drawing::bInit = FALSE;
bool Drawing::bDisplay = false;

Servers server_manager;

HRESULT Drawing::hkPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flag)
{
    if (!Hook::swap_chain)
    {
        Hook::swap_chain = pThis;
    }

    if (!bInit)
    {
        InitImGui(pThis);
    }

    if (GetAsyncKeyState(VK_END) & 1)
    {
        Hook::unhook_directx();
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, Hook::hmodule, 0, nullptr);
        return Hook::original_present(pThis, SyncInterval, Flag);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (!bDisplay && !functions::sub_0xDF4D69BF(structures::FIRST) && functions::sub_0xDF4D694F(structures::FIRST))
    {
        static ImVec2 find_match_min = ImVec2(80, 200);
        static ImVec2 find_match_max = ImVec2(280, 254);

        POINT cursor_pos;
        GetCursorPos(&cursor_pos);
        ScreenToClient(Hook::hwnd, &cursor_pos);
        ImVec2 mouse_pos = ImVec2((float)cursor_pos.x, (float)cursor_pos.y);

        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) &&
            mouse_pos.x >= find_match_min.x && mouse_pos.x <= find_match_max.x &&
            mouse_pos.y >= find_match_min.y && mouse_pos.y <= find_match_max.y)
        {
            bDisplay = true;
        }       

        *(int*)(Engine::offset(0xC94B4DDA)) = 1;
    }
  
    else if (bDisplay && !functions::sub_0xDF4D69BF(structures::FIRST) && functions::sub_0xDF4D694F(structures::FIRST))
    {
        if (!helper::are_we_host())
        {
            bDisplay = false;  
            *(int*)(Engine::offset(0xC94B4DDA)) = 1; 
        }

        else
        {
            ImVec2 screen_size = ImVec2((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));

            ImGui::SetNextWindowSize(screen_size, ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

            ImGui::Begin("Nidavellir overlay", &bDisplay, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            {
                server_manager.draw_server_list();
            }
            ImGui::End();

            static float last_fetch_time = 0.0f;
            float current_time = (float)ImGui::GetTime();

            if (current_time - last_fetch_time >= 0.1200f)
            {
                server_manager.fetch_sessions();
                last_fetch_time = current_time;
            }

            *(int*)(Engine::offset(0xC94B4DDA)) = 0;
        }
    }

    else
    {
        *(int*)(Engine::offset(0xC94B4DDA)) = 1;
        bDisplay = false;
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return Hook::original_present(pThis, SyncInterval, Flag);
}

void Drawing::InitImGui(IDXGISwapChain* pSwapChain)
{
    Hook::hook_window();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.Fonts->AddFontDefault();

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(Hook::hwnd);

    pSwapChain->GetDevice(__uuidof(Hook::device), (void**)&Hook::device);
    Hook::device->GetImmediateContext(&Hook::device_context);

    ImGui_ImplDX11_Init(Hook::device, Hook::device_context);

    bInit = TRUE;
}
