#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

/**
 * @brief main - The main loop of the program.
 *
 * @param argc - The number of arguments passed to the program.
 * @param argv - The arguments passed to the program.
 *
 * @return int - 0 if the program runs successfully, 1 if not.
 */
int main(int argc, char *argv[])
{
    // Initialize the SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize Video Subsystem! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window with the name "Pongy"
    SDL_Window *window = SDL_CreateWindow("Pongy", 800, 600, 0);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main game loop
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}