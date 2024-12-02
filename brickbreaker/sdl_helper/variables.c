#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "variables.h"


// Paramètres de la fenêtre et du renderer
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
char* name = "SDL app";




// Paramètres du texte et des polices
/*
Pour rajouter des polices d'écriture:
(0. Téléchargez le fichier .ttf de votre police et mettez-le dans le fichier "fonts")
1. Rajouter une variable dans variable.h pour la police, par exemple: "extern TTF_Font* [nom]_[taille];"
2. Rajouter une variable ci dessous du même nom, sans le mot clé "extern" ("TTF_Font* [nom]_[taille];")
3. Rajouter un assignement à cette variable dans la fonction constantsLoadFont()
exemple: [nom]_[taille] = TTF_OpenFont("sdl_helper/fonts/[nom].ttf", [taille]);
*/

// Initialisation des variables
TTF_Font* comfortaaFont_16;
TTF_Font* comfortaaFont_18;
TTF_Font* comfortaaFont_24;
TTF_Font* comfortaaFont_28;
TTF_Font* comfortaaFont_36;
TTF_Font* comfortaaFont_52;

// Fonction qui sera appelé pour charger les polices dans les variables
void constantsLoadFont() {
    comfortaaFont_16 = TTF_OpenFont("sdl_helper/fonts/Comfortaa-Regular.ttf", 16);
    comfortaaFont_18 = TTF_OpenFont("sdl_helper/fonts/Comfortaa-Regular.ttf", 18);
    comfortaaFont_24 = TTF_OpenFont("sdl_helper/fonts/Comfortaa-Regular.ttf", 24);
    comfortaaFont_28 = TTF_OpenFont("sdl_helper/fonts/Comfortaa-Regular.ttf", 28);
    comfortaaFont_36 = TTF_OpenFont("sdl_helper/fonts/Comfortaa-Regular.ttf", 36);
    comfortaaFont_52 = TTF_OpenFont("sdl_helper/fonts/Comfortaa-Regular.ttf", 52);
}

SDL_Color textColor = {255, 0, 0, 255};
