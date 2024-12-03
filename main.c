#include <stdio.h>
#include <SDL.h>

/**
 * @brief main - The main loop of the program.
 * 
 * @param argc - The number of arguments passed to the program.
 * @param argv - The arguments passed to the program.
 * 
 * @return int - 0 if the program runs successfully, 1 if not.
 */
int main(int argc, char* argv[]) {
    // Initialize the SDL library
    SDL_Init(SDL_INIT_EVERYTHING);
    // Create a window with the name "Pongy"
    SDL_Window *window = SDL_CreateWindow("Pongy",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    // Get the surface of the window
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    // Create player 1 and player 2's rectangles
    const SDL_Rect player1Rect = {20, 30, 20, 70};
    const SDL_Rect player2Rect = {760, 30, 20, 70};
    // Create a color
    const Uint32 color = 0xffffffff;
    // Fill the rectangles with the color
    SDL_FillRect(screen, &player1Rect, color);
    SDL_FillRect(screen, &player2Rect, color);
    // Update the window surface
    SDL_UpdateWindowSurface(window);
    // Pause for 5 seconds
    SDL_Delay(5000);
    // Quit the SDL library
    SDL_Quit();
    // Return 0 if the program runs successfully
    return 0;
}