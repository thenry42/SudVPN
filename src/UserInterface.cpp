#include "UserInterface.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

UserInterface::UserInterface(): running(true) {}

UserInterface::~UserInterface() {}

int UserInterface::init(void)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        return (-1);
    
    // Create window with graphics context
    window_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("SudVPN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 800, window_flags);
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

    // Load Images
    LoadTextureFromFile(LOGO_IMG, &logo_texture, &logo_width, &logo_height, renderer);

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
            ImGui::MenuItem("Account Information");
            ImGui::MenuItem("Help");
            if (ImGui::MenuItem("Exit"))
                running = false;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Locations"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    //STYLE
    setCustomStyle();

    // MAIN WINDOW CONTENT
    if (ImGui::CollapsingHeader("Account Information", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::SeparatorText("Account Information");
        ImGui::NewLine();
        if (nv.isLogged() == true)
        {
            ImGui::Text("Email Address: %s", nv.getEmail().c_str());
            ImGui::Text("Username: %s", nv.getVpnService().c_str());
        }
        else
        {
            ImGui::Text("You need to be logged in to access account information.");
        }
        ImGui::NewLine();
    }

    if (ImGui::CollapsingHeader("Actions", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::SeparatorText("Status");
        if (nv.isLogged() == true)
            ImGui::Text("You are logged in");
        else
        {
            ImGui::Text("You are not logged in");
            if (ImGui::Button("Login"))
                nv.login();
            ImGui::SameLine();
            if (nv.isWaitingCallbackLink() == true)
            {
                ImGui::InputTextWithHint(" ", "enter text here", nv.buffer, 512);
                nv.setCallbackLink(nv.buffer);
                nv.loginCallback();
            }
            ImGui::NewLine();
        }
        if (nv.isWaitingCallbackLink() == false && nv.isLogged() == true)
        {
            if (nv.isConnected() == true)
                ImGui::Text("You are connected");
            else
            {
                ImGui::Text("You are not connected");
                ImGui::SameLine();
                if (ImGui::Button("Connect"))
                    nv.connect();
            }
        }
        ImGui::NewLine();
    }
    
    if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Firewall", &nv._firewall);
        ImGui::Checkbox("Routing", &nv._routing);
        ImGui::Checkbox("Analytics", &nv._analytics);
        ImGui::Checkbox("Kill Switch", &nv._killSwitch);
        ImGui::Checkbox("Threat Protection Lite", &nv._ThreatProtectionLite);
        ImGui::Checkbox("Auto-connect", &nv._autoConnect);
        ImGui::Checkbox("IPv6", &nv._IPv6);
        ImGui::Checkbox("Meshnet", &nv._meshnet);
        ImGui::Checkbox("DNS", &nv._dns);
        ImGui::Checkbox("LAN Discovery", &nv._lanDiscovery);
        ImGui::NewLine();
    }

    // SUDVPN LOGO
    ImGui::SetCursorPosX((io.DisplaySize.x - logo_width) / 2);
    ImGui::SetCursorPosY((io.DisplaySize.y - logo_width) - 50);
    ImGui::Image(logo_texture, ImVec2(logo_width, logo_height));

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

bool UserInterface::LoadTextureFromFile(const char* filename, SDL_Texture** texture_ptr, int* width, int* height, SDL_Renderer* renderer) {
    int channels;
    unsigned char* data = stbi_load(filename, width, height, &channels, 0);

    if (data == nullptr) {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        return false;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)data, *width, *height, channels * 8, channels * *width,
                                                    0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    if (surface == nullptr) {
        fprintf(stderr, "Failed to create SDL surface: %s\n", SDL_GetError());
        return false;
    }

    *texture_ptr = SDL_CreateTextureFromSurface(renderer, surface);

    if ((*texture_ptr) == nullptr) {
        fprintf(stderr, "Failed to create SDL texture: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    stbi_image_free(data);

    return true;
}

void UserInterface::setCustomStyle(void)
{
    // Get the current ImGui style
    ImGuiStyle& style = ImGui::GetStyle();

    // Set custom style parameters
    //style.WindowRounding = 5.0f;
    //style.FrameRounding = 4.0f;
    //style.ScrollbarRounding = 12.0f;

    ImColor Main_color = ImColor(254, 138, 156, 200);
    ImColor Hovered_color = ImColor(254, 138, 156, 255);
    ImColor Active_color = ImColor(254, 138, 156, 255);

    // Set custom colors
    ImVec4* colors = style.Colors;
    //colors[ImGuiCol_Text] = ImVec4(1.0f, 0, 1.0f, 1.0f);
    colors[ImGuiCol_Separator] = Main_color;
    //colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 1.00f);
    colors[ImGuiCol_Button] = Main_color;
    colors[ImGuiCol_ButtonHovered] = Hovered_color;
    colors[ImGuiCol_ButtonActive] = Active_color;
    colors[ImGuiCol_MenuBarBg] = Main_color;
    colors[ImGuiCol_ScrollbarBg] = Main_color;
    
    colors[ImGuiCol_Header] = Main_color;
    colors[ImGuiCol_HeaderHovered] = Hovered_color;
    colors[ImGuiCol_HeaderActive] = Active_color;
    colors[ImGuiCol_CheckMark] = Main_color;
}