#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <iostream>
#include "TicTacToe.hpp"
#include "Pong.hpp"
#include "Arcanoid.hpp"

SDL_Window* Window = nullptr;
SDL_Renderer* Renderer = nullptr;
TTF_TextEngine* Engine = nullptr;
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
/*
SDL_Texture* texture = nullptr;
texture = IMG_LoadTexture(Renderer, "../assets/imgs/circle.png");
SDL_RenderTexture(Renderer, texture, NULL, NULL);
*/
void init(void) {
  if(!SDL_Init(SDL_INIT_VIDEO)) std::cout<<"Error initializing video.\n";
  if(!SDL_CreateWindowAndRenderer("Sgames", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &Window, &Renderer)) std::cout<<"Error creating window and renderer.\n";
  if (!TTF_Init()) std::cout << "TTF_Init failed: " << SDL_GetError();

  Engine=TTF_CreateRendererTextEngine(Renderer);
  if(!Engine) std::cout<<"Error creating text enginge: "<<SDL_GetError();
}
void end(void){
  SDL_DestroyWindow(Window);
  SDL_DestroyRenderer(Renderer);
  Window = NULL;
  Renderer = NULL;
  SDL_Quit();
}
//------------------------------------------------------------------------------------------//
void renderDefault(void){
  SDL_SetRenderDrawColor(Renderer, 0, 20, 100, 255);
  SDL_RenderClear(Renderer);
  SDL_RenderPresent(Renderer);
}
void loop(void){
  bool quit = false;
  SDL_Event e;
  SDL_zero(e);

  while(!quit){ 
    renderDefault();
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_QUIT) quit = true;
      if(e.type == SDL_EVENT_KEY_DOWN) switch(e.key.key){
        case SDLK_ESCAPE:
          quit=true;
          break;
        case SDLK_1:
          TicTacToe();
          break;
        case SDLK_2:
          Pong::Pong();
          break;
        case SDLK_3:
          Arcanoid::Game();
          break;
      }
    }
  }
}
int main(void){
  init();
  loop();
  end();
  return 0;
}
