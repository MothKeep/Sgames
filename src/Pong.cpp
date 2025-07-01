#include <SDL3/SDL_error.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

//1080x720
extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
TTF_TextEngine* Engine = nullptr;
SDL_Texture* boinkT = nullptr;
SDL_Texture* ballT = nullptr;

void moveBall(float& speed, float& x, float& y, float& dir_x, float& dir_y, float left_y, float right_y, float& fspeed){
  x += speed * dir_x;
  y += speed * dir_y;
  // side bouncing
  if(y<40 || y>680){
    y-= speed * dir_y;
    dir_y=-dir_y;
  }
  
  //simple boinker bounce
  if(x>62 && x<67 && y>left_y - 48 && y<left_y + 48){
    x-= speed * dir_x;
    dir_y = (y - left_y)  / 48;
    dir_x = std::sqrt(1 - dir_y*dir_y);
    x += speed * dir_x;
    speed += 0.003;
    fspeed += 0.003;
  }
  else if(x>1013 && x<1018 && y>right_y - 48 && y<right_y + 48){
    x-= speed * dir_x;
    dir_y = (y - right_y)  / 48;
    dir_x = - std::sqrt(1 - dir_y*dir_y);
    x += speed * dir_x;
    speed += 0.003;
    fspeed += 0.003;
  }
  if(x > 1096 || x < -16) y = -500;
}

void PongRenderFrame(float left_y, float right_y, float ball_x, float ball_y, TTF_Text* lScore, TTF_Text* rScore){
  SDL_SetRenderDrawColor(Renderer, 20, 20, 20, 255);
  SDL_RenderClear(Renderer);
  SDL_SetRenderDrawColor(Renderer, 120, 120, 120, 255);
  SDL_RenderLine(Renderer, 540, 40, 540, 680);
  
  SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
  TTF_DrawRendererText(lScore, 200, 80);
  TTF_DrawRendererText(rScore, 800, 80);
  
  SDL_FRect* l = new SDL_FRect{40, left_y-32, 11, 64};
  SDL_RenderTexture(Renderer, boinkT, NULL, l);

  SDL_FRect* r = new SDL_FRect{1029, right_y-32, 11, 64};
  SDL_RenderTexture(Renderer, boinkT, NULL, r);
  
  SDL_FRect* b = new SDL_FRect{ball_x-16, ball_y-16, 32, 32};
  SDL_RenderTexture(Renderer, ballT, NULL, b);



  SDL_RenderPresent(Renderer);
}

void Pong(){

  const bool* inputs = SDL_GetKeyboardState(NULL);
  float left_y = 360, right_y = 360, ball_x= 540, ball_y=360, dir_x, dir_y, speed=0.02, fspeed=0.03;
  int lS=0, rS=0;
  
  bool left_start = false;
  dir_x = (float)(rand()%50 + 51) / 100;
  dir_y = std::sqrt(1 - dir_x * dir_x);

  boinkT = IMG_LoadTexture(Renderer, "../assets/imgs/boinker.png");
  ballT = IMG_LoadTexture(Renderer, "../assets/imgs/ball.png");
  if(ballT == NULL || boinkT == NULL)std::cout<<"Error loading texture: "<<SDL_GetError()<<"\n";

  Engine=TTF_CreateRendererTextEngine(Renderer);
  TTF_Font* font = TTF_OpenFont("../assets/fonts/Font.ttf", 24);
  if(!font) std::cout<<"error at: "<<SDL_GetError();
  TTF_Text* lScore = TTF_CreateText(Engine, font, std::to_string(lS).c_str(), std::to_string(lS).length());
  TTF_Text* rScore = TTF_CreateText(Engine, font, std::to_string(rS).c_str(), std::to_string(rS).length());

  bool quit = false;  
  SDL_Event e;
  SDL_zero(e);
  
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
    moveBall(speed, ball_x, ball_y, dir_x, dir_y, left_y, right_y, fspeed);
    if(ball_y == -500){
      if(ball_x<0){
        rS += 1;
        rScore = TTF_CreateText(Engine, font, std::to_string(rS).c_str(), std::to_string(rS).length());
      }
      else{
        lS += 1;
        lScore = TTF_CreateText(Engine, font, std::to_string(lS).c_str(), std::to_string(lS).length());
      }
      left_start = !left_start;
      ball_x = 540;
      ball_y = 360;
      dir_x = (float)(rand()%50 + 51) / 100;
      dir_y = std::sqrt(1 - dir_x * dir_x);
      if(left_start) dir_x = - dir_x;
      speed = 0.02;
      fspeed = 0.03;
    };
    if(inputs[SDL_SCANCODE_W] && left_y > 40) left_y-=fspeed;
    if(inputs[SDL_SCANCODE_S] && left_y < 680) left_y+=fspeed;
    if(inputs[SDL_SCANCODE_UP] && right_y > 40) right_y-=fspeed;
    if(inputs[SDL_SCANCODE_DOWN] && right_y < 680) right_y+=fspeed;

    PongRenderFrame(left_y, right_y, ball_x, ball_y, lScore, rScore);
  }
}
