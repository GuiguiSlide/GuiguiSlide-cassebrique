#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "variables.h"
#include "audio_functions.h"


void audioInitializeMixer() {
    /** @brief Fonction d'initialisation du mixer */

    // Initialise la librairie d'audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL audio n'a pas pu s'initialiser. SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Initialise le mixeur
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer n'a pas pu s'initialiser. SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Allouer des channels
    Mix_AllocateChannels(MAX_AUDIO_CHANNELS);
}


void audioSimpleLoadAndPlay(char* file) {
    /** @brief Charge et joue un audio sur le premier channel libre
     *  @param :file:, le fichier .wav à jouer
    */
    // Utilise la même fonction, mais avec -1 pour jouer l'audio sur le premier channel de libre
    audioLoadAndPlay(file, -1);
}


void audioLoadAndPlay(char* file, int channel) {
    /** @brief Charge et joue un audio sur le channel défini par l'utilisateur
     *  @param :file:, le fichier .wav à jouer
     *  @param :channel:, le channel sur lequel jouer l'audio
    */

    // Charger le son
    Mix_Chunk* sound = Mix_LoadWAV(file);
    if (!sound) {
        printf("Erreur lors du chargement du son: %s\n", Mix_GetError());
        return;
    }

    // Jouer l'audio sur le channel voulu
    Mix_PlayChannel(channel, sound, 0);
}


// Ferme et libère la mémoire du mixer
void audioCleanup() {
    Mix_CloseAudio();
}

