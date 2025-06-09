#include <SDL3/SDL_error.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cstddef>
#include <iostream>

//1080x720
extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
SDL_Texture* boinkT = nullptr;

void PongRenderFrame(float left_y, float right_y, float ball_x, float ball_y){
  SDL_SetRenderDrawColor(Renderer, 20, 20, 20, 255);
  SDL_RenderClear(Renderer);
  SDL_SetRenderDrawColor(Renderer, 120, 120, 120, 255);
  SDL_RenderLine(Renderer, 540, 40, 540, 680);
  
  SDL_FRect* l = new SDL_FRect{40, left_y, 11, 64};
  SDL_RenderTexture(Renderer, boinkT, NULL, l);

  SDL_FRect* r = new SDL_FRect{1029, right_y, 11, 64};
  SDL_RenderTexture(Renderer, boinkT, NULL, r);

  SDL_RenderPresent(Renderer);
}

void Pong(){
  bool quit = false;  
  SDL_Event e;
  SDL_zero(e);
  const bool* inputs = SDL_GetKeyboardState(NULL);

  float left_y = 540, right_y = 540, ball_x= 360, ball_y=540;
  
  boinkT = IMG_LoadTexture(Renderer, "../assets/imgs/boinker.png");
  if(boinkT == NULL)std::cout<<"Error loading texture: "<<SDL_GetError()<<"\n";

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
    if(inputs[SDL_SCANCODE_W] && left_y > 40) left_y-=0.03;
    if(inputs[SDL_SCANCODE_S] && left_y < 720 - 40 - 64 ) left_y+=0.03;
    if(inputs[SDL_SCANCODE_UP] && right_y > 40) right_y-=0.03;
    if(inputs[SDL_SCANCODE_DOWN] && right_y < 720 - 40 - 64) right_y+=0.03;
    PongRenderFrame(left_y, right_y, ball_x, ball_y);
  }
}
