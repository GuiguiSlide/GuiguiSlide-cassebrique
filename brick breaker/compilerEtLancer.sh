#!/bin/bash


# Définit le nom de fichier en sortie
output_file="main.out"

# Définit les librairies à utiliser
librairies="-lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer"

# Trouve tout les fichier de code en .c et les ajoute à la variable c_files.
c_files=$(find . -type f -name "*.c")

# Compile les fichiers .c dans un fichier .out
gcc $c_files -o $output_file $librairies

# Vérifie que la compilation a réussi
if [ $? -eq 0 ]; then
    echo "Compilation réussie. Lancement du programme..."

    # Lancer le .out
    ./$output_file
else
    echo "Erreur lors de la compilation."
fi
