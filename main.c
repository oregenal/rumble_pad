#include <stdio.h>

#include <SDL2/SDL.h>

#define LOW_FREQUENCY_RUMBLE 0x0
#define HIGH_FREQUENCY_RUMBLE 0xFFFF
#define DURATION_MS 50

int main(void)
{
	if(SDL_Init(SDL_INIT_JOYSTICK) < 0) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_GameController *gamePad1 = NULL;

	int num_of_joys = SDL_NumJoysticks();

	if(num_of_joys < 1) {
		fprintf(stderr, "No gamepad connected\n");
		return EXIT_FAILURE;
	} else {
		gamePad1 = SDL_GameControllerOpen(0);
		const char *gamePad1_name = SDL_GameControllerName(gamePad1);
		printf("%s connected.\n", gamePad1_name);
		if(!SDL_GameControllerHasRumble(gamePad1)) {
			fprintf(stderr, "%s has no rumble.\n", gamePad1_name);
			return EXIT_FAILURE;
		}
	}

	SDL_GameControllerRumble(gamePad1, 
			LOW_FREQUENCY_RUMBLE, 
			HIGH_FREQUENCY_RUMBLE, 
			DURATION_MS);

	SDL_Delay(DURATION_MS*2);

	SDL_GameControllerRumble(gamePad1, 0x0, 0x0, 50);

	SDL_Delay(100);

	return 0;
}
