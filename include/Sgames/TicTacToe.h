#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <bitset>
#include <cstdint>

bool changeField(bool sign, uint8_t field, std::bitset<18>& GameMap);
uint8_t returnSign(uint8_t field, std::bitset<18>& GameMap);
bool isVictorious(std::bitset<18>& GameMap);

void drawMap(std::bitset<18>& GameMap);
void TicTacToe();

#endif // TICTACTOE_H
