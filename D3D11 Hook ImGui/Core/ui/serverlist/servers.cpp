#include "servers.h"

structures::MatchMakingQuery query_info{};
std::vector<structures::MatchMakingInfo> sessions;
std::array<structures::MatchMakingInfo, 500> search_results;

const auto lobby_search_success_callback = [](structures::TaskRecord* task)
{
        const auto remote_task = task->remoteTask;

        if (!remote_task) return;

        for (size_t i = 0; i < remote_task->numResults; ++i)
        {
            const auto result = &search_results[i];

            if (result->info.hostAddrSize != sizeof(structures::XNADDR) || result->isEmpty == 1)
                continue;

            auto it = std::find_if(sessions.begin(), sessions.end(), [&](const auto& session)
            {
                    return session.xuid == result->xuid;
            });

            if (it == sessions.end())
            {
                sessions.push_back(*result);
            }
            else
            {
                *it = *result;
            }
        }
};

const auto lobby_search_failure_callback = [](structures::TaskRecord* task)
{
    
};

const structures::TaskDefinition task_lobby_search = 
{
    2,
    "t71",
    0x10,
    lobby_search_success_callback,
    lobby_search_failure_callback
};

void Servers::fetch_sessions()
{
    if (functions::sub_0xDC86B3CF(&task_lobby_search))
        return;

    functions::sub_0xDC87455F(&task_lobby_search);

    const auto task = functions::sub_0xDC8743FF(&task_lobby_search, structures::FIRST, nullptr, 10000);
    if (!task) return;

    const auto matchmaking = functions::sub_0xDFE90C3F(0);
    if (!matchmaking) return;

    query_info.queryId = structures::SEARCH_SESSIONS_BY_SERVER_TYPE;
    query_info.serverType = 2000;

    structures::bdRemoteTask* remote_task{};

    functions::sub_0xDC3D181F
    (
        matchmaking,
        &remote_task,
        query_info.queryId,
        0,
        search_results.size(),
        &query_info,
        search_results.data()
    );

    if (!remote_task)
    {
        functions::sub_0xDC86B63F(task);
        return;
    }

    task->remoteTask = remote_task;
    functions::sub_0xDC86B28F(task);
}

void Servers::draw_server_list()
{
    functions::sub_0xDFE96C0F(&query_info, 0, true);

    functions::sub_0xDC698243
    (
        &search_results,
        sizeof(structures::MatchMakingInfo),
        search_results.size(),
        Engine::offset(0xDFE974EF),
        Engine::offset(0xDC768E8F)
    );

    static char filterText[128] = "";

    ImGui::InputText("Search by IP or XUID", filterText, IM_ARRAYSIZE(filterText));
    ImGui::SameLine();

    if (ImGui::Button("Clear"))
    {
        memset(filterText, 0, sizeof(filterText));
        sessions.clear();
    }

    ImGui::SameLine();

    if (ImGui::Button("Search"))
    {
        fetch_sessions();
    }

    if (ImGui::BeginTable("ServerList", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("IP Address", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("XUID", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Skill Rating", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Ping", ImGuiTableColumnFlags_WidthFixed, 50.0f); 
        ImGui::TableSetupColumn("Players", ImGuiTableColumnFlags_WidthFixed, 70.0f);  

        ImGui::TableHeadersRow();

        std::vector<structures::MatchMakingInfo> sorted_sessions{ sessions };

        std::sort(sorted_sessions.begin(), sorted_sessions.end(), [](const auto& a, const auto& b)
        {
                if (a.info.maxPlayers != b.info.maxPlayers)
                {
                    return a.info.maxPlayers > b.info.maxPlayers;
                }

                else
                {
                    return a.info.numPlayers > b.info.numPlayers;
                }
        });

        for (const auto& session : sorted_sessions)
        {
            const auto host_info = session.get_host_info();
            const auto xnaddr = host_info.serializedAdr.xnaddr;
            const auto netadr = helper::XNADDR_to_string(&xnaddr);

            long long host_xuid = selfmade_functions::function_two(1);

            bool matches_filter = true;

            if (strlen(filterText) > 0 &&
                strstr(netadr.c_str(), filterText) == nullptr &&
                strstr(std::to_string(session.xuid).c_str(), filterText) == nullptr)
            {
                matches_filter = false;
            }

            if (matches_filter)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();

                if (session.xuid == host_xuid)
                {
                    ImVec4 textColor = ImVec4(ImColor(80, 120, 180, 255));
                    ImGui::PushStyleColor(ImGuiCol_Text, textColor);

                    ImGui::Selectable(netadr.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);

                    ImGui::PopStyleColor();
                }

                else
                {
                    if (ImGui::Selectable(netadr.c_str(), false, ImGuiSelectableFlags_SpanAllColumns))
                    {
                        selfmade_functions::function_one(host_info);
                    }
                }
           
                ImGui::TableNextColumn();
                ImGui::Text("%llu", session.xuid);

                const char* skill_label = "Low";

                if (session.skill > -470)
                {
                    skill_label = "Medium";
                }
                if (session.skill > -800)
                {
                    skill_label = "High";
                }

                ImGui::TableNextColumn();
                ImGui::Text("%s", skill_label);

                ImGui::TableNextColumn();
                ImGui::Text("%d", session.latencyBand);

                ImGui::TableNextColumn();
                ImGui::Text("%d/%d", session.info.numPlayers, session.info.maxPlayers);
            }
        }

        ImGui::EndTable();
    }
}



