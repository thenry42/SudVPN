#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "imgui.h"
#include <SDL2/SDL.h>
#include "NordVPN.hpp"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#define LOGO_IMG "utils/minilogo.png"

class UserInterface {
    
    public:
        
        bool running;
        
        ImGuiIO* io;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_WindowFlags window_flags;

        // Image (logo)
        SDL_Texture* logo_texture;
        int logo_width;
        int logo_height;

        UserInterface();
        ~UserInterface();
        
        int     init(void);
        void    render(void);
        void    destroy(void);
        void    update(NordVPN& nv);

        bool    LoadTextureFromFile(const char* filename, SDL_Texture** texture_ptr, int* width, int* height, SDL_Renderer* renderer);
        void    setCustomStyle(void);  
};

#endif