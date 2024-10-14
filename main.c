#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 920
#define FPS 60



int x = 0;
int y = 0;
int tableau_bb[5][3];
int tableau_x;
int tableau_y;

void tableau(){
  for(tableau_x=1;tableau_x<=5;tableau_x++){
    for(tableau_y=1;tableau_y<=3;tableau_y++){
      tableau_bb[tableau_x][tableau_y]=1;
      printf("%d %d %d \n", tableau_x, tableau_y, tableau_bb[tableau_x][tableau_y]);
    }
  }
}

void init_game(){
tableau();
}
void rectangle_tab(){
  for(tableau_x=1;tableau_x<=5;tableau_x++){
    for(tableau_y=1;tableau_y<=3;tableau_y++){
      if(tableau_bb[tableau_x][tableau_y]==1){
      drawRect(tableau_x,tableau_y,100,50);
  }}}
}
void drawGame(){

    clear();
    rectangle_tab();
    changeColor(255,255,0);
    drawCircle(100,100,100);
    actualize();
    usleep(1000000 / FPS); 
}
void KeyPressed(SDL_Keycode touche){

    switch (touche) {

        case SDLK_q:

            printf("Q\n");
            x--;
            break;
        case SDLK_d:

            printf("D\n");
            x++;
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }

        drawGame();
    }
}

int main(){

    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}
