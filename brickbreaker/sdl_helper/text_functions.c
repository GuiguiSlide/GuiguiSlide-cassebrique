#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "variables.h"
#include "text_functions.h"


void textInitializeTtfLibrary() {
    /** @brief Fonction pour initialiser la librairie de texte */

    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
    }
}


void textChangeColor(int colorR, int colorG, int colorB, int colorAlpha) {
    /** @brief Fonction pour changer la couleur du texte et sa transparence
     *  @param :colorR:, R pour la teinte en rouge
     *  @param :colorG:, G pour la teinte en vert
     *  @param :colorB:, B pour la teinte en bleu
     *  @param :colorAlpha:, alpha pour changer la transparence (255 = visible, 0 = transparent)
    */
    textColor.r = colorR;
    textColor.g = colorG;
    textColor.b = colorB;
    textColor.a = colorAlpha;
}


void textDrawText(char* textToDraw, int destinationX, int destinationY, TTF_Font* font) {
    /** @brief Fonction qui affiche un texte à un emplacement voulu et une police définie par l'utilisateur
     *  @param :textToDraw:, la chaine de caractère à dessiner
     *  @param :destinationX:, la position X de l'emplacement où mettre le texte
     *  @param :destinationY:, la position Y de l'emplacement où mettre le texte
     *  @param :font:, la police d'écriture
    */

    // Vérifie que la police d'écriture existe
    if (font == NULL) {
        printf("Erreur: police d'écriture inexistante. (:param: font == NULL)");
        return;
    }

    // Crée une surface avec le texte de l'utilisateur
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textToDraw, textColor);
    if (textSurface == NULL) {
        printf("TTF_RenderText_Solid erreur: %s\n", TTF_GetError());
        return;
    }

    // Crée une texture à partir de la surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (textTexture == NULL) {
    printf("Erreur: échec de la création de la texture du texte à partir sa surface. SDL Error: %s\n", SDL_GetError());
    }

    // Définir la sortie du texte en un rectangle avec la longueur et largeur du texte
    int textureWidth = 0;
    int textureHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_Rect destinationRect = {destinationX, destinationY, textureWidth, textureHeight};

    // Copier le texte sur le renderer et libérer la mémoire ensuite
    SDL_RenderCopy(renderer, textTexture, NULL, &destinationRect);
    SDL_DestroyTexture(textTexture);
}

