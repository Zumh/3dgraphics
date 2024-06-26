#include "display.h"
#include "vector.h"

#define N_POINTS  9 * 9 * 9
vec3_t cube_points[N_POINTS];
float fov_factor = 640;
bool is_running = false;
vec2_t projected_points[N_POINTS];
vec3_t camera_position = {.x = 0, .y = 0, .z = -5}; 
void setup(void);
void process_input(void);
void update(void);
void render(void);


int main(void){

	printf("Hello, world!\n");
	// TODO: Crate a SDL window
	is_running = initialize_window();

	setup();
	
	while(is_running){
		process_input();
		update();
		render();
	}	
	destroy_window();
	return 0;
}



void setup(void){
	// Allocate the required memory in bytes to hold the color buffer
	color_buffer = (uint32_t*) malloc( WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));
	// Creating a SDL texture that is used to display
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	int point_count = 0;
	// Start loading my array of vectors
	// From -1 to 1 (in this 9x9x9 cube)
	for (float x = -1; x <= 1; x += 0.25){
		for (float y = -1; y <= 1; y += 0.25){
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t new_point = {.x = x, .y = y, .z = z};	
				cube_points[point_count++] = new_point;
			}
		}	
	}
	
}
void process_input(void){

	// start reading event from keyboard
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE){
				is_running = false;
			}
			break;
	}
}

// Function that recieves a 3D vector and returns a projected 2D point
vec2_t project(vec3_t point){
	// px = py/pz
	// py = px/pz
	vec2_t projected_point = {
		.x = (fov_factor * point.x)/point.z,
		.y = (fov_factor * point.y)/point.z
	};

	return projected_point;
}

void update(void){
	for( int i = 0; i < N_POINTS; i++){
		vec3_t point = cube_points[i];

		// move the points away from the camera 
		point.z -= camera_position.z;
		
		// Project the current point
		// remove all the z and return 2d
		vec2_t projected_point = project(point);

		// Save the projected 2D vector in the array of projected points
		projected_points[i] = projected_point;
	}
}




void 
render(void){
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);
	draw_grid();
	
	// Loop all projected points and render them
	for(int i = 0; i < N_POINTS; i++){
		vec2_t projected_point = projected_points[i];
		draw_rect(
			projected_point.x + (WINDOW_WIDTH /2), 
			projected_point.y + (WINDOW_HEIGHT/2),
			4,
			4,
			0xFFFFF00
		);
	}
	
	//draw_pixel(20, 20, 0xFFFFFF00);
	//draw_rect(300, 200, 300, 150, 0xFFFF00FF);
	render_color_buffer();
	// copy this to sdl texture
	//clear_color_buffer(0xFFFFFF00);
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);

}



