# SDL_lib_v2+

# A installer:
- SDL2 (sudo apt-get install libsdl2-dev)
- SDL2_mixer (sudo apt-get install libsdl2-mixer-dev)
- SDL2_ttf (sudo apt-get install libsdl2-ttf-dev)

# Ce qu'il y'a en plus de la version précédente de SDL_lib_v2:
- Gestion de l'audio
- Gestion de textes

# Un petit exemple!
## Pour compiler le fichier exemple.c:
- Pour la simplicité d'utilisation la commande de compilation est directement dans un script bash!
- Se placer dans SDL_lib_v2-master, et taper la commande:
- ./compilerEtLancer.sh



# Comment set-up la librairie?
- Rien de plus simple, il suffit de mettre le fichier sdl_helper entier dans le répertoire de votre projet.


# Et comment s'en servir?

## En haut de votre fichier contenant la fonction main:
- Pour tout inclure:   #include "sdl_helper/sdlhelper.h"



# Comment se servir de la librairie:

## Les fonctions sont classées en "rubriques". Elles commencent par:
- "text" pour une commande concernant du texte
- "audio" pour une commande concernant de l'audio

## Pour changer la couleur du texte, et ensuite écrire quelque chose:
- textChangeColor(int r, int g, int b, int a)
- Paramètre r: le taux de rouge (de 0 à 255)
- Paramètre g: le taux de vert (de 0 à 255)
- Paramètre b: le taux de bleu (de 0 à 255)
- Paramètre a: le taux du canal alpha (de 0 à 255). Cela gère l'opacité du texte. Donc de 0 pour transparent à 255 pour totalement visible.

- textDrawText(char* texte, int positionX, int postionY, TTF_Font* policeEcriture)
- Paramètre texte: le texte à écrire
- Paramètre positionX: la position X du texte
- Paramètre positionY: la position Y du texte
- Paramètre policeEcriture: la police d'écriture à utiliser. Par defaut j'en ai créé 6: comfortaaFont_16, comfortaaFont_18, comfortaaFont_24, comfortaaFont_28, comfortaaFont_36, comfortaaFont_52. (Le chiffre signifie la taille (en px) de la police.)

### Pour rajouter des polices, un tutoriel est disponible dans variables.c, ligne 16

### Pour voir un exemple de comment sont appelées ces fonctions dans un programme, voir exemple.c, fonction drawGame().


## Pour jouer un audio:
- audioLoadAndPlay(char* cheminVersFichierWAV, int channel)
- Paramètre cheminVersFichierWAV: votre chemin d'accès vers le fichier audio
- Paramètre channel: le channel audio sur lequel votre audio doit être joué (voir note 1)

### NOTE 1:
- Un channel peut jouer UN SEUL audio à la fois, d'où la nécessité d'en avoir plusieurs si on veut que plusieurs sont puissent être joués en même temps.
- Par défaut, j'ai défini ce nombre à 64. Mais, vous pouvez le changer dans le fichier constants.h, ligne 19: #define MAX_AUDIO_CHANNELS (int)
- De plus, en passant comme paramètre -1, l'audio sera joué sur le premier channel de libre.

## Sinon, la fonction audioSimpleLoadAndPlay(char* cheminVersFichierWAV) mettra tout seul le premier channel de libre.

### NOTE 2:
- Pour correctement "éteindre" le gestionnaire de son, il faut appeller la commande audioCleanup().
- Je l'ai rajouté à la fonction freeAndTerminate() déjà existante.
- Mais, si vous avez une autre manière pour quitter l'application, il serait préférable d'ajouter cette fonction également.

### Pour voir un exemple de la fonction _audio_loadAndPlay(), voir exemple.c, fonction gameLoop(), case SDL_MOUSEBUTTONUP.


# FIN
