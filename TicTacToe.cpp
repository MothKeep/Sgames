#include <bitset>
#include <cstdint>
#include <iostream>

// 00 00 00 00 00 00 00 00 00
/* 00 - empty 01 - x 10 - o
  00 00 00
  00 00 00
  00 00 00
 */
std::bitset<18> GameMap = 0;
// sign: true = x false = o
bool changeField(bool sign, uint8_t field){
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

uint8_t returnSign(uint8_t field) {
  if(GameMap[field*2-1]) return 1;
  else if (GameMap[field*2-2]) return 2;
  else return 0;
}

bool isVictorious(void){
  //horizontal, vertical
  for(int i=0;i<7;i+=3){
    if(GameMap[i*2] && GameMap[(i+1)*2] && GameMap[(i+2)*2]) return true;
    if(GameMap[i*2+1] && GameMap[(i+1)*2+1] && GameMap[(i+2)*2+1]) return true;
  }
  //diagonal
  if((GameMap[0] && GameMap[8] && GameMap[16]) || (GameMap[1] && GameMap[9] && GameMap[17])) return true;
  if((GameMap[4] && GameMap[8] && GameMap[12])  || (GameMap[5] && GameMap[9] && GameMap[13])) return true;
  return false;
}

int main(void){
  
}
