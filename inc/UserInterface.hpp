#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "imgui.h"
#include <SDL2/SDL.h>
#include "NordVPN.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

class UserInterface {
    
    public:
        
        bool running;
        SDL_WindowFlags window_flags;
        SDL_Window* window;
        SDL_Renderer* renderer;
        ImGuiIO* io;

        UserInterface();
        ~UserInterface();
        int init(void);
        void update(NordVPN& nv);
        void render(void);
        void destroy(void);

};

#endif