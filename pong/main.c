#include <SDL2/SDL.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_helper/sdlhelper.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60

//points/vie/debut
int points=0;
int start=2;
int lifes=3;

//positions
int xplat=WINDOW_WIDTH/2;
int yplat=WINDOW_HEIGHT-WINDOW_HEIGHT/10;
int xplat2=WINDOW_WIDTH/2;
int yplat2=20;
int vxb;
int vyb;
int xb;
int yb;

//collisions
int droiteplatform2;int gaucheplatform2;int basplatform2;int hautplatform2;
int droiteplatform;int gaucheplatform;int basplatform;int hautplatform;
int droiteball ;int gaucheball ;int basball ;int hautball ;

void lifebar(){
  if(lifes==3){
    sprite(WINDOW_WIDTH-100,WINDOW_HEIGHT-50,"bmp/3lifes.bmp");
  }
  if(lifes==2){
    sprite(WINDOW_WIDTH-100,WINDOW_HEIGHT-50,"bmp/2lifes.bmp");
  }
  if(lifes==1){
    sprite(WINDOW_WIDTH-100,WINDOW_HEIGHT-50,"bmp/1lifes.bmp");
  }
}
//menu de fin
void endscreen(){
  if(points>=75){
    start=-1;
    clear();
    sprite(0,0,"bmp/goodend.bmp");
  }
  if(lifes==0){
  start=-1;
  clear();
  sprite(0,0,"bmp/badend.bmp");
  audioLoadAndPlay("sounds/death.wav",1);
  }
}
//menu de commencement
void startmenu(){ 
    if(start == 2){
      clear();
      sprite(0,0,"bmp/menu1.bmp");
      actualize();
    }
    if(start == 1){
      clear();
      sprite(0,0,"bmp/menu2.bmp");
      actualize();
    }
}
//collisions platforme
void colplat(){

  droiteplatform = xplat+120;//haut droite
  gaucheplatform = xplat;//haut gauche
  basplatform = yplat+30;//bas gauche
  hautplatform = yplat;//haut gauche

  droiteplatform2 = xplat2+120;//haut droite
  gaucheplatform2 = xplat2;//haut gauche
  basplatform2 = yplat2+30;//bas gauche
  hautplatform2 = yplat2;//haut gauche

  gaucheball  = xb;//haut gauche
  droiteball  = xb+30;//haut droite
  basball  = yb+30;//bas gauche/(basball -5=centreb)
  hautball  = yb;//haut gauche

  //collisions  de la plateforme
    if( vyb > 0 ){
      if((gaucheball <= droiteplatform && gaucheball >= gaucheplatform )||( droiteball <= droiteplatform && droiteball >= gaucheplatform)){
        if(basball >= hautplatform && basball <= basplatform){
            vyb = vyb * -1;  
            audioLoadAndPlay("sounds/throw.wav",-1);      
        }
      }
    }
    if( vyb < 0 ){
        if((gaucheball <= droiteplatform && gaucheball  >= gaucheplatform) || (droiteball <= droiteplatform && droiteball >= gaucheplatform)){
            if(hautball <= basplatform && hautball >= hautplatform){
                vyb = vyb * -1;    
                audioLoadAndPlay("sounds/throw.wav",-1);               
          }
     }
  }
    if( vyb > 0 ){
      if((gaucheball <= droiteplatform2 && gaucheball >= gaucheplatform2 )||( droiteball <= droiteplatform2 && droiteball >= gaucheplatform2)){
        if(basball >= hautplatform2 && basball <= basplatform2){
            vyb = vyb * -1; 
            audioLoadAndPlay("sounds/throw.wav",-1);       
        }
      }
    }
    if( vyb < 0 ){
        if((gaucheball <= droiteplatform2 && gaucheball  >= gaucheplatform2) || (droiteball <= droiteplatform2 && droiteball >= gaucheplatform2)){
            if(hautball <= basplatform2 && hautball >= hautplatform2){
                vyb = vyb * -1; 
                audioLoadAndPlay("sounds/throw.wav",-1);                  
          }
     }
  }

}
//rebonds de la balle et mouvement
void mouv_balle(){// ball
  yb=yb+vyb;
  xb=xb+vxb;
  if(vyb  <  0){
    if(yb < 5){
      vyb = 0;
      vxb = 0;
      yb = WINDOW_HEIGHT/2;
      xb = WINDOW_WIDTH/2;
      lifes=lifes-1;
    }
  }
  if(vyb  >  0){
    if(yb+30 > WINDOW_HEIGHT){
      vyb = 0;
      vxb = 0;
      yb = WINDOW_HEIGHT/2;
      xb = WINDOW_WIDTH/2;
      lifes=lifes-1;
    }
  }
  if(vxb  <  0){
    if(xb+2 < 5){
      vxb =  vxb  * -1;
    }
  }
  if(vxb  >  0){
    if(xb+30 > WINDOW_WIDTH){
      vxb =  vxb  * -1;
    }
  }
}
//boucle qui tourne une seule fois
void init_game(){
  yb = yplat-20;
  xb = xplat+60;  
  audioLoadAndPlay("sounds/gamemusic.wav",1);
}
//grand reset    
void reset(){    
    if(start == 3){
      clear();
      int points=0;
      int start=2;
      int lifes=3;
      int xplat=WINDOW_WIDTH/2;
      int yplat=WINDOW_HEIGHT-WINDOW_HEIGHT/10;
        yb = yplat-20;
        xb = xplat+60;  
      start = 2;
      actualize();
    }
}
//boucle qui tourne jusqua que le jeu se finnisse
void drawGame(){ 
    clear();
    startmenu();
    if(start == 0){
      sprite(0,0,"bmp/vamopalaplaya.bmp");
      lifebar();
      sprite(xplat2,yplat2,"bmp/beacon.bmp");// 120/30 taille platform
      sprite(xplat,yplat,"bmp/beacon.bmp");// 120/30 taille platform
      sprite(xb,yb,"bmp/slave.bmp"); // 10/10 taille balle
      colplat();
      mouv_balle();
      endscreen();
      reset();
      actualize();
    }
    usleep(1000000 / FPS); 
}
void KeyPressed(SDL_Keycode touche){
    switch (touche) {
        case SDLK_g:
            if(start >= 0){
              start = start-1;
            }
            else if(start == -1){
              clear();
              start = 3;
              reset();
            }
            break;
        case SDLK_SPACE:
            vyb = 3;
            vxb = 3;
            break;
        case SDLK_p:
            printf("%d\n",points);
            break;        
        case SDLK_LEFT:
            if(xplat>2){
              xplat = xplat - 5;
            }
            break;
        case SDLK_RIGHT:
            if(xplat<WINDOW_WIDTH-120){
              xplat = xplat + 5;
            }
            break;
        case SDLK_UP:
            vyb = vyb +1;
            vxb = vxb +1;
            break;
        case SDLK_DOWN:
            vyb = vyb -1;
            vxb = vxb -1;
            break;
        case SDLK_q:
            if(xplat>2){
              xplat2 = xplat2 - 5;
            }
            break;
        case SDLK_d:
            if(xplat<WINDOW_WIDTH-120){
              xplat2 = xplat2 + 5;
            }
            break;
        case SDLK_b:
            xplat = xb -60;
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
            switch (event.type){
                case SDL_QUIT:
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    xb=event.motion.x - 15;
                    yb=event.motion.y - 15;
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
    }
