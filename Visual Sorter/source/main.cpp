#include <SDL.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string>
#include <Windows.h>
#include <iostream>
int x = 0;
int i = 0;
int line = 0;
int array[768];
int j;
int temp;

int main(int argc, char* argv[])
{

	//Key press surfaces constants
	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};

	std::fstream file;
	file.open("list.txt");
	while (file >> temp) {
		array[i] = temp;
		i++;
	}

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		SDL_Surface* screenSurface;

		

		if (SDL_CreateWindowAndRenderer(1450, 800, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			screenSurface = SDL_GetWindowSurface(window);

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

				x = 0;
				for (int number : array) {
					SDL_RenderDrawLine(renderer, x, 1050, x, 1050 - (number * 2));
					x += 5;

				}



				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
					else if (event.type == SDL_KEYDOWN) {
						for (i = 0; i < 768; i++) {
							for (j = i + 1; j < 768; j++)
							{
								if (array[j] < array[i]) {
									temp = array[i];
									array[i] = array[j];
									array[j] = temp;

								}
							}
						}
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}

//int main(int argc, char* args[])
//{
//	//Start up SDL and create window
//	if (!init())
//	{
//		printf("Failed to initialize!\n");
//	}
//	else
//	{
//		//Load media
//		{
//			//Main loop flag
//			bool quit = false;
//
//			//Event handler
//			
//
//			//While application is running
//			while (!quit)
//			{
//				//Handle events on queue
//				while (SDL_PollEvent(&e) != 0)
//				{
//					//User requests quit
//					if (e.type == SDL_QUIT)
//					{
//						quit = true;
//					}
//				}
//
//				SDL_RenderDrawLine()
//
//				//Update the surface
//				SDL_UpdateWindowSurface(gWindow);
//			}
//		}
//	}
//
//	//Free resources and close SDL
//	close();
//
//	return 0;
//}