#include "imgui.h"
#include <SDL2/SDL.h>
#include "NordVPN.hpp"
#include "imgui_impl_sdl2.h"
#include "UserInterface.hpp"
#include "imgui_impl_sdlrenderer2.h"

// draw.io to draw a flow chart

int main(void)
{
	NordVPN nv;
	UserInterface ui;

	// Initialize the UserInterface
	if (ui.init() == -1)
		return (EXIT_FAILURE);
	
	// Main loop
	while (ui.running)
	{
		// Handle events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				ui.running = false;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(ui.window))
				ui.running = false;
		}

		// Start the frame
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Update the UserInterface
		ui.update(nv);

		// Render the UserInterface
		ui.render();
	}

	// Destroy the UserInterface
	ui.destroy();

	return (EXIT_SUCCESS);
}
