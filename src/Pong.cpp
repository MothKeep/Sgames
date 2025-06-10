#include <SDL3/SDL_error.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>

//1080x720
extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
SDL_Texture* boinkT = nullptr;
SDL_Texture* ballT = nullptr;

void moveBall(float speed, float& x, float& y, float& dir_x, float& dir_y, float left_y, float right_y){
  x += speed * dir_x;
  y += speed * dir_y;
  
  // side bouncing
  if(y<40 || y>680){
    y-= speed * dir_y;
    dir_y=-dir_y;
  }
  
  //simple boinker bounce (todo: speed acceleration | relative angle bounce)
  if((x<67 && y>left_y - 16 && y<left_y + 16) || (x>1013 && x>right_y - 16 && y<right_y+ 16)){
    x-= speed * dir_x;
    dir_x = -dir_x;
    // also it causes funny stuff rn - ball may go inside boinker causing weird effects
  }

  if(x > 1096 || x < -16) y = -500;
}

void PongRenderFrame(float left_y, float right_y, float ball_x, float ball_y){
  SDL_SetRenderDrawColor(Renderer, 20, 20, 20, 255);
  SDL_RenderClear(Renderer);
  SDL_SetRenderDrawColor(Renderer, 120, 120, 120, 255);
  SDL_RenderLine(Renderer, 540, 40, 540, 680);
  
  SDL_FRect* l = new SDL_FRect{40, left_y-32, 11, 64};
  SDL_RenderTexture(Renderer, boinkT, NULL, l);

  SDL_FRect* r = new SDL_FRect{1029, right_y-32, 11, 64};
  SDL_RenderTexture(Renderer, boinkT, NULL, r);
  
  SDL_FRect* b = new SDL_FRect{ball_x-16, ball_y-16, 32, 32};
  SDL_RenderTexture(Renderer, ballT, NULL, b);

  SDL_RenderPresent(Renderer);
}

void Pong(){
  bool quit = false;  
  SDL_Event e;
  SDL_zero(e);
  const bool* inputs = SDL_GetKeyboardState(NULL);

  float left_y = 360, right_y = 360, ball_x= 540, ball_y=360, dir_x=0.4, dir_y=0.6;
  boinkT = IMG_LoadTexture(Renderer, "../assets/imgs/boinker.png");
  ballT = IMG_LoadTexture(Renderer, "../assets/imgs/ball.png");
  if(ballT == NULL || boinkT == NULL)std::cout<<"Error loading texture: "<<SDL_GetError()<<"\n";

  while(!quit){ 
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_KEY_DOWN){
        switch(e.key.key){
          case SDLK_ESCAPE:
            quit=true;
            break;
        }
      }        
    }
    moveBall(0.08, ball_x, ball_y, dir_x, dir_y, left_y, right_y);
    if(ball_y == -500){
      //if(x<0) right scored
      //else left scored
      //add some function waiting few secs and showing score
      ball_x = 540;
      ball_y = 360;
      dir_x = (float)(rand()%50 + 51) / 100;
      dir_y = std::sqrt(1 - dir_x * dir_x);
    };
    if(inputs[SDL_SCANCODE_W] && left_y > 40) left_y-=0.03;
    if(inputs[SDL_SCANCODE_S] && left_y < 680) left_y+=0.03;
    if(inputs[SDL_SCANCODE_UP] && right_y > 40) right_y-=0.03;
    if(inputs[SDL_SCANCODE_DOWN] && right_y < 680) right_y+=0.03;

    PongRenderFrame(left_y, right_y, ball_x, ball_y);
  }
}
