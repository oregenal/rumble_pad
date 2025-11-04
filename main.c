#include <stdio.h>

#include <SDL2/SDL.h>

#define LOW_FREQUENCY_RUMBLE 0xFFFF
#define HIGH_FREQUENCY_RUMBLE 0x0
#define DURATION_MS 200
#define RUMBLE_TIMES 3
#define DUALSHOCK "PS4 Controller"

Uint16 low = LOW_FREQUENCY_RUMBLE, high = HIGH_FREQUENCY_RUMBLE;
Uint32 duration = DURATION_MS, times = RUMBLE_TIMES;

void error_exit(const char *msg)
{
	fprintf(stderr, msg);
	SDL_Quit();
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
		error_exit(SDL_GetError());

	SDL_GameController *gamePad = NULL;

	int num_of_joys = SDL_NumJoysticks();

	if(num_of_joys < 1) {
		error_exit("No gamepad connected\n");
	} else {
		for (int i = 0; i < num_of_joys; ++i) {
			gamePad = SDL_GameControllerOpen(i);
			if(SDL_GameControllerHasRumble(gamePad)) {
				break;
			} else {
				gamePad = NULL;
			}
		}
	}

	if (!gamePad)
		error_exit("No rumble gamepad connected\n");

	if (5 == argc) {
		sscanf(argv[1], "%hx", &low);
		sscanf(argv[2], "%hx", &high);
		sscanf(argv[3], "%u", &duration);
		sscanf(argv[4], "%u", &times);
	}

	for(Uint32 i = 0; i < times; ++i) {
		SDL_GameControllerRumble(gamePad, low, high, duration);

		SDL_Delay(duration);

		SDL_GameControllerRumble(gamePad, 0x0, 0x0, 
				duration <= 200 ? duration : 200);

		SDL_Delay(duration <= 200 ? duration : 200);
	}

	SDL_Quit();
	return 0;
}
