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
	} else {
		printf("SDL GamePad ready to go!\n");
	}

	SDL_GameController *gamePad1 = NULL;

	if(SDL_NumJoysticks() < 1) {
		fprintf(stderr, "No gamepad connected\n");
		return EXIT_FAILURE;
	} else {
		printf("%d gamepad connected.\n", SDL_NumJoysticks());
		gamePad1 = SDL_GameControllerOpen(0);
		//printf("GamepadID: %d.\n", SDL_JoystickInstanceID(gamePad1));
		if(SDL_GameControllerHasRumble(gamePad1)) {
			printf("Gamepad has rumble.\n");
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
