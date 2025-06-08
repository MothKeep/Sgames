#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>

//-----------------------------------------------------------------------------------------------------//
bool changeField(bool sign, uint8_t field, std::bitset<18>& GameMap){
  if(GameMap[field*2-1] || GameMap[field*2-2]) return false;
  if(sign){
    GameMap[field*2-1]=1;
    return true;
  }
  else{
    GameMap[field*2-2]=1;
    return true;
  }
}

/*
uint8_t returnSign(uint8_t field, std::bitset<18>& GameMap) {
  if(GameMap[field*2-1]) return 1;
  else if (GameMap[field*2-2]) return 2;
  else return 0;
}*/

bool isVictorious(std::bitset<18> GameMap){
  //horizontal, vertical
  for(int i=0;i<7;i+=3){
    if(GameMap[i*2] && GameMap[(i+1)*2] && GameMap[(i+2)*2]) return true;
    if(GameMap[i*2+1] && GameMap[(i+1)*2+1] && GameMap[(i+2)*2+1]) return true;
  }
  //diagonal
  //  -x -- --    -- -x --    -- -- -x
  if((GameMap[0] && GameMap[8] && GameMap[16]) || (GameMap[1] && GameMap[9] && GameMap[17])) return true;
  if((GameMap[4] && GameMap[8] && GameMap[12])  || (GameMap[5] && GameMap[9] && GameMap[13])) return true;
  return false;
}
//-----------------------------------------------------------------------------------------------------//
//
extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
SDL_Texture* cirT = nullptr;
SDL_Texture* xT = nullptr;

void drawMap(std::bitset<18>& GameMap){

  SDL_SetRenderDrawColor(Renderer, 20, 20, 20, 255);
  SDL_RenderClear(Renderer);
  SDL_SetRenderDrawColor(Renderer, 180, 180, 180, 255);
  SDL_RenderLine(Renderer, 540 - 240 , 360 - 80, 540 + 240, 360 - 80);
  SDL_RenderLine(Renderer, 540 - 240 , 360 + 80, 540 + 240, 360 + 80);
  SDL_RenderLine(Renderer, 540 - 80, 360 - 240, 540 - 80, 360 + 240);
  SDL_RenderLine(Renderer, 540 + 80, 360 - 240, 540 + 80, 360 + 240);
  for(uint8_t field=0; field<9; field++){
    float x = 540-240 + field%3 * 160;
    float y = 360-240 + field/3 * 160;
    SDL_FRect* a = new SDL_FRect{x+10,y+10,140.0f,140.0f};
    
    if(GameMap[(field+1)*2-2]) SDL_RenderTexture(Renderer, cirT, NULL, a);
    else if(GameMap[(field+1)*2-1]) SDL_RenderTexture(Renderer, xT, NULL, a);
  }
}

// 00 00 00 00 00 00 00 00 00
/* 00 - empty 01 - x 10 - o
  00 00 00
  00 00 00
  00 00 00
 */

void TicTacToe(){
  cirT = IMG_LoadTexture(Renderer, "../assets/imgs/circle.png");
  xT = IMG_LoadTexture(Renderer, "../assets/imgs/x.png");
  if(cirT == NULL || xT == NULL) std::cout<<"Error loading textures\n"<<SDL_GetError();
  
  // sign: true = x false = o
  bool sign = true;
  bool quit = false;
  std::bitset<18> GameMap = 0;
  SDL_Event e;
  SDL_zero(e);
    
  SDL_SetRenderDrawColor(Renderer, 20, 20, 20, 255);
  SDL_RenderClear(Renderer);
  drawMap(GameMap);
  SDL_RenderPresent(Renderer);
  
  while(!quit){ 
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_EVENT_KEY_DOWN) switch(e.key.key){
        case SDLK_ESCAPE:
          quit=true;
          break;
      }
      if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        float mouse_x, mouse_y;
        uint8_t r = 0, c = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        
        if(mouse_x > 300.0f){
          if(mouse_x < 460.0f) r = 1;
          else if(mouse_x < 620.0f) r = 2;
          else if(mouse_x < 780.0f) r = 3;
          if(mouse_y > 120.0f){
            if(mouse_y < 280.0f) c = 1;
            else if(mouse_y < 440.0f) c = 2;
            else if(mouse_y < 600.0f) c = 3;
          }
        }

        if(r!=0 && c!=0){
          if(changeField(sign, r + (c-1)*3, GameMap)){
            drawMap(GameMap);
            
            if(isVictorious(GameMap)){
              if(sign) SDL_SetRenderDrawColor(Renderer, 180, 80, 80, 255);
              else SDL_SetRenderDrawColor(Renderer, 80, 80, 180, 255);
              SDL_RenderClear(Renderer);
            }

            SDL_RenderPresent(Renderer);
            sign = !sign;
          }
        }
      }
    }
  }

}
