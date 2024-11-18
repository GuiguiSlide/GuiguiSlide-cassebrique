#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include <SDL2/SDL_ttf.h>
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
int vxb;
int vyb;
int xb;
int yb;

//tableau
int tableau_x;
int tableau_y;
int tableau_bb[14][8];

//collisions
int droiteplatform;int gaucheplatform;int basplatform;int hautplatform;
int droiteball ;int gaucheball ;int basball ;int hautball ;
int droitebrique;int gauchebrique;int basbrique;int hautbrique;
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

void xpbar(){
  if(points>=0&&points<=10){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar1sur7.bmp");
  }
  if(points>=10&&points<=20){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar2sur7.bmp");
  }
  if(points>=20&&points<=30){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar3sur7.bmp");
  }
  if(points>=30&&points<=40){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar4sur7.bmp");
  }
  if(points>=40&&points<=50){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar5sur7.bmp");
  }
  if(points>=50&&points<=60){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar6sur7.bmp");
  }
  if(points>=60&&points<=70){
    sprite(10,WINDOW_HEIGHT-210,"bmp/bar7sur7.bmp");
  }
  if(points>70){
  sprite(0,0,"bmp/boom.bmp");
  }
}

//menu de fin
void endscreen(){
  if(points>=78){
    start=-1;
    clear();
    sprite(0,0,"bmp/goodend.bmp");
  }
  if(lifes==0){
  start=-1;
  clear();
  sprite(0,0,"bmp/badend.bmp");
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

gaucheball  = xb;//haut gauche
droiteball  = xb+30;//haut droite
basball  = yb+30;//bas gauche/(basball -5=centreb)
hautball  = yb;//haut gauche

//collisions  
  if( vyb == 3 ){
    if((gaucheball  <= droiteplatform && gaucheball  >= gaucheplatform )||( droiteball  <= droiteplatform && droiteball  >= gaucheplatform)){
      if(basball >= hautplatform && basball <= basplatform){
          vyb = vyb * -1;        
      }
    }
  }
  if( vyb == -3 ){
      if((gaucheball  <= droiteplatform && gaucheball  >= gaucheplatform) || (droiteball  <= droiteplatform && droiteball  >= gaucheplatform)){
          if(hautball  <= basplatform && hautball  >= hautplatform){
              vyb = vyb * -1;                   
          }
     }
  }
}

//collisions briques
void colbrik(){
    for(tableau_x = 1;tableau_x <=  14;tableau_x++){
      for(tableau_y = 1;tableau_y <= 7;tableau_y++){
          if(tableau_bb[tableau_x][tableau_y] == 1){
  
  //collisions de la balle
        droiteball  = xb+30;
        basball  = yb+30;
        hautball  = yb;
        gaucheball = xb;
   
   //collisions de la brique
        droitebrique = tableau_x*50;
        basbrique = tableau_y*50;
        hautbrique = tableau_y;
        gauchebrique = tableau_x;
    
    //collisions
          if( droiteball <= droitebrique + 50 && gaucheball >= gauchebrique ){
              if( hautball <= basbrique + 50 && hautball >= basbrique + 50 + vyb ){
                if( vyb == -3 ){
                   vyb = vyb * -1;
                   tableau_bb[tableau_x][tableau_y] = 0;
                   printf("%d\t%d\t%d\t%d\t%d\t was_destroyed from bottom\n",tableau_bb[tableau_x][tableau_y],tableau_y*50,tableau_x*50,yb,xb);
                   points=points+1;
                } 
             }
          if( basball <= hautbrique && basball >= hautbrique + vyb ){
             if( vyb == 3 ){
                vyb = vyb * -1;
                tableau_bb[tableau_x][tableau_y] = 0;
                printf("%d\t%d\t%d\t%d\t%d\t was_destroyed from top\n",tableau_bb[tableau_x][tableau_y],tableau_y*50,tableau_x*50,yb,xb);
                points=points+1;
             }
          }
        }
       if(hautball  <= basbrique+50 && basball >= hautbrique ){
          if(droiteball  <= gauchebrique && droiteball >= gauchebrique + vxb ){
            if(vxb == 3){
               vxb = vxb * -1;
               tableau_bb[tableau_x][tableau_y] = 0;
               printf("%d\t%d\t%d\t%d\t%d\t was_destroyed from left\n",tableau_bb[tableau_x][tableau_y],tableau_y*50,tableau_x*50,yb,xb);
               points=points+1;
             }
           }
           if(gaucheball  <= droitebrique +50 && gaucheball >= droitebrique + 50 +vxb){
             if(vxb == -3){
                 vxb = vxb * -1;
                 tableau_bb[tableau_x][tableau_y] = 0;
                 printf("%d\t%d\t%d\t%d\t%d\t was_destroyed from right\n",tableau_bb[tableau_x][tableau_y],tableau_y*50,tableau_x*50,yb,xb);
                 points=points+1;
            }
          }
        }
      }
    }
  }
}

//rebonds de la balle et mouvement
void mouv_balle(){// ball
  yb=yb+vyb;
  xb=xb+vxb;
  if(vyb  ==  -3){
    if(yb <= 4){
      vyb =  vyb  * -1;
    }
  }
  if(vyb  ==  3){
    if(yb+30 >= WINDOW_HEIGHT){
      vyb = 0;
      vxb = 0;
      yb = yplat-20;
      xb = xplat+60;
      lifes=lifes-1;
    }
  }
  if(vxb  ==  -3){
    if(xb+2 <= 4){
      vxb =  vxb  * -1;
    }
  }
  if(vxb  ==  3){
    if(xb+30 >= WINDOW_WIDTH){
      vxb =  vxb  * -1;
    }
  }
}

//crée un tableau 
void tableau(){ 
  for(tableau_x=1;tableau_x <= 14;tableau_x++){
    for(tableau_y=1;tableau_y <= 7;tableau_y++){
      tableau_bb[tableau_x][tableau_y] = 1;
    }
  }
}

//utilise le tableau pour dessiner les briques
void square_tab(){
    for(tableau_x=1;tableau_x <= 14;tableau_x++){
        for(tableau_y=1;tableau_y <= 7;tableau_y++){
          if(tableau_bb[tableau_x][tableau_y] == 1){
            sprite(tableau_x * 50, tableau_y*50, "bmp/brick.bmp");// 50/50 taille brique
         }
       }
    }
}

//boucle qui tourne une seule fois
void init_game(){
  yb = yplat-20;
  xb = xplat+60;  
  tableau();
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
      int tableau_bb[14][8];
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
      xpbar();
      square_tab();
      sprite(xplat,yplat,"bmp/beacon.bmp");// 120/30 taille platform
      sprite(xb,yb,"bmp/slave.bmp"); // 10/10 taille balle
      colplat();
      colbrik();
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
            if(start != 0){
              start = start-1;
            }
            if(start == -1){
              clear();
              start = 3;
              lifes = 3;
              tableau();
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
        case SDLK_q:
            if(xplat>2){
              xplat = xplat - 5;
            }
            break;
        case SDLK_d:
            if(xplat<WINDOW_WIDTH-120){
              xplat = xplat + 5;
            }
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
                    yb=event.motion.x;
                    xb=event.motion.y;
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
