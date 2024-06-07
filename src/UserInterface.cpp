#include "UserInterface.hpp"

UserInterface::UserInterface(): running(true) {}

UserInterface::~UserInterface() {}

int UserInterface::init(void)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        return (-1);
    
    // Create window with graphics context
    window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("SudVPN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr)
        return (-1);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        return (-1);
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
   	(*io).ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	(*io).ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	(*io).IniFilename = NULL; 

    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    return (0);
}

void UserInterface::update(NordVPN& nv)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver); 

    static bool no_titlebar = true;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = true;
    static bool no_resize = true;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool unsaved_document = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
    if (no_close)           running = NULL; // Don't pass our bool* to Begin

    // DO NOT REMOVE
    if (!ImGui::Begin("SudVPN <3", &running, window_flags))
    {
        ImGui::End();
        return ;
    }

    // MENU BAR
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::MenuItem("Firewall");
            ImGui::MenuItem("Routing");
            ImGui::MenuItem("Analytics");
            ImGui::MenuItem("Kill Switch");
            ImGui::MenuItem("Threat Protection Lite");
            ImGui::MenuItem("Auto-connect");
            ImGui::MenuItem("IPv6");
            ImGui::MenuItem("Meshnet");
            ImGui::MenuItem("DNS");
            ImGui::MenuItem("LAN Discovery");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Main Window Content
    ImGui::SeparatorText("Status");

    ImGui::Text("%s", (nv.isLogged() ? "Yes" : "No"));
    if (ImGui::Button("Login"))
        nv.login();

    (void)nv;

    // DO NOT REMOVE
    ImGui::End();
}

void UserInterface::render(void)
{
    ImGui::Render();
    SDL_RenderSetScale(renderer, (*io).DisplayFramebufferScale.x, (*io).DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}

void UserInterface::destroy(void)
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}