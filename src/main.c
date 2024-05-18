#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool initialize_window(void);

int main(void){

	printf("Hello, world!\n");
	// TODO: Crate a SDL window
	initialize_window();
	
	return 0;
}


bool initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
	}
	// Create a SDL Window
	window = SDL_CreateWindow(

		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);

	if (!window){
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	// Create a SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){
		fprintf(stderr, "Error creating SDL renderer.\n");	
		return false;
	}
	return true;
}
