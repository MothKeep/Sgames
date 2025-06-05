#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <cstdint>

bool changeField(bool sign, uint8_t field);
uint8_t returnSign(uint8_t field);
bool isVictorious(void);

#endif // TICTACTOE_H
