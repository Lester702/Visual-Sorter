#include <SDL.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string>
//#include <Windows.h>
#include <iostream>
#include <vector>

int x = 0;
int i = 0;
int array[2000];
int j;
int temp;

int main(int argc, char* argv[])
{
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

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

	int n = sizeof(array) / sizeof(array[0]);

	std::vector<int> vec(array, array + n);

	file.close();

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		SDL_Surface* screenSurface;

		

		if (SDL_CreateWindowAndRenderer(1850, 1000, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			screenSurface = SDL_GetWindowSurface(window);

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);
				

				SDL_SetRenderDrawColor(renderer, 0, 125, 242, SDL_ALPHA_OPAQUE);

				x = 0;
				for (int number : array) {
					SDL_RenderDrawLine(renderer, x, 1000, x, 1000 - (number * 0.5));
					x += 1;

				}



				SDL_RenderPresent(renderer);

				while (SDL_PollEvent(&event) != 0)
				{
					//User requests quit
					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
				}

				//Set texture based on current keystate
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_SPACE])
				{
					printf("Space was pressed\n");
					printf("%i", vec.size());

					for (i = 0; i < 2000; i++) {
						for (j = i + 1; j < 2000; j++)
						{
							if (array[j] < array[i]) {
								temp = array[i];
								array[i] = array[j];
								array[j] = temp;
							}
						}
					}

					//for (i = 0; i < 2000; i++) {
					//	for (j = i + 1; j < 2000; j++)
					//	{
					//		if (array[j] < array[i]) {
					//			temp = array[i];
					//			array[i] = array[j];
					//			array[j] = temp;
					//		}
					//	}
					//}
				}
				else if (currentKeyStates[SDL_SCANCODE_R])
				{
					std::fill_n(array, i, 0);
					file.open("list.txt");
					i = 0;
					while (file >> temp)
					{
						array[i] = temp;
						i++;
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
