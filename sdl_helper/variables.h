#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 920
#define FPS 60


extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern char* name;


// Gestion du son
#define MAX_AUDIO_CHANNELS 64

// Gestion du texte
extern SDL_Color textColor;
extern TTF_Font* comfortaaFont_16;
extern TTF_Font* comfortaaFont_18;
extern TTF_Font* comfortaaFont_24;
extern TTF_Font* comfortaaFont_28;
extern TTF_Font* comfortaaFont_36;
extern TTF_Font* comfortaaFont_52;
void constantsLoadFont();
