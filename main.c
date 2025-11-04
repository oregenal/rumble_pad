#include <stdio.h>

#include <SDL2/SDL.h>

#define LOW_FREQUENCY_RUMBLE 0xFFFF
#define HIGH_FREQUENCY_RUMBLE 0x0
#define DURATION_MS 200
#define RUMBLE_TIMES 3
#define DUALSHOCK "PS4 Controller"

Uint16 low = LOW_FREQUENCY_RUMBLE, high = HIGH_FREQUENCY_RUMBLE;
Uint32 duration = DURATION_MS, times = RUMBLE_TIMES;

int main(int argc, char **argv)
{
	if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_GameController *gamePad = NULL;

	int num_of_joys = SDL_NumJoysticks();

	if(num_of_joys < 1) {
		fprintf(stderr, "No gamepad connected\n");
		return EXIT_FAILURE;
	} else {
		gamePad = SDL_GameControllerOpen(0);
		const char *gamePad_name = SDL_GameControllerName(gamePad);
		if(!strcmp(gamePad_name, DUALSHOCK))
			printf("DualShock connected.\n");
		else
			printf("%s connected.\n", gamePad_name);
		if(!SDL_GameControllerHasRumble(gamePad)) {
			fprintf(stderr, "%s has no rumble.\n", gamePad_name);
			return EXIT_FAILURE;
		}
	}

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

	SDL_Delay(100);

	SDL_Quit();

	return 0;
}
