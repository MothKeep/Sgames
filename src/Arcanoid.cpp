#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <sys/types.h>
#include <vector>
#include "Arcanoid.hpp"

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;

namespace Arcanoid{
  SDL_Texture* boinkT = nullptr;
  SDL_Texture* ballT = nullptr;
  SDL_Texture* brickT = nullptr;
  
  std::vector<SDL_FRect*> Map; //16 x 10

  void RenderFrame(float ppos, float bpos_x, float bpox_y){
    SDL_SetRenderDrawColor(Renderer, 40, 100, 50, 255);
    SDL_RenderClear(Renderer);
  
    //SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    //TTF_DrawRendererText(Score, 50, 50); 
    
    //660 - height of player platform
    SDL_FRect* player = new SDL_FRect{ppos-32, 660, 64, 11};
    SDL_RenderTexture(Renderer, boinkT, NULL, player);

    SDL_FRect* ball = new SDL_FRect{bpos_x-8, bpox_y-8, 16, 16};
    SDL_RenderTexture(Renderer, ballT, NULL, ball);
    
    for(int16_t i=0; i<Map.size();i++){
      SDL_RenderTexture(Renderer, brickT, NULL, Map[i]);
    }
    SDL_RenderPresent(Renderer);
  }

  void GenerateMap(){
    for(u_int8_t i=0; i<10; i++){
      for(u_int8_t j=0; j<16; j++){
        if(rand()%2){
          //28 16*64 28 (1080)
          SDL_FRect* rect = new SDL_FRect{ 28.f+j*64, 28.f+i*28, 64, 28};
          Map.push_back(rect);
        }
      }
    }
  }

  bool BrickHit(float bx, float by){ //checks if ball hit any brick
    for(u_int16_t i=0; i<Map.size(); i++){
      float x = Map[i]->x, y = Map[i]->y;
      if(bx+8>x && bx-8<x + 64 && by+8>y && by-8<y+11){
        Map.erase(Map.begin()+i);
        return true;
      }
    }
    return false;
  }
  void BallMovement(float& bx, float& by, float& dirx, float& diry, float ppos){
    bx += dirx*0.03;
    by += diry*0.03;
  
    if(by>660 - 8 && by<671 && ppos-bx<40 && ppos-bx>-40){
      by -= diry*0.03;
      dirx=(bx-ppos) / 40;
      diry= - std::sqrt(1-dirx*dirx);
      
      bx += dirx*0.03;
      by += diry*0.03;
    }

    if(BrickHit(bx, by) || by<8)diry=-diry;
    
    if(bx>1072 || bx < 8) dirx=-dirx;
  }
  void Game(){
    boinkT = IMG_LoadTexture(Renderer, "../assets/imgs/boinker_h.png");
    ballT = IMG_LoadTexture(Renderer, "../assets/imgs/ball.png");
    brickT = IMG_LoadTexture(Renderer, "../assets/imgs/brick.png");
    
    const bool* inputs = SDL_GetKeyboardState(NULL);
    float player_pos = 540, ball_x = 540, ball_y = 360, dirx=0, diry=1, pspeed=0.03;
    
    GenerateMap();

    bool quit = false;  
    SDL_Event e;
    SDL_zero(e);
    
    while(!quit){
      // managing exit
      while(SDL_PollEvent(&e)){
        if(e.type == SDL_EVENT_KEY_DOWN){
          switch(e.key.key){
            case SDLK_ESCAPE:
              quit=true;
              break;
          }
        }         
      }
      
      if(inputs[SDL_SCANCODE_A] && player_pos > 40) player_pos-=pspeed;
      if(inputs[SDL_SCANCODE_D] && player_pos < 1040) player_pos+=pspeed;
      BallMovement(ball_x, ball_y, dirx, diry, player_pos);

      RenderFrame(player_pos, ball_x, ball_y);
    }
  }
}
