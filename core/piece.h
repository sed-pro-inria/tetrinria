#ifndef TRN_PIECE_H
#define TRN_PIECE_H

#include <stddef.h>
#include <stdbool.h>

#include "tetromino.h"

#include <malloc.h>

#define SPACE_DIMENSION 2

typedef struct piece
{
  TrnTetrominoType type;
  TrnPositionInGrid topLeftCorner;
  int angle;
} TrnPiece;

TrnPiece* trn_piece_new();
TrnPiece trn_piece_create(TrnTetrominoType const type,
                          int topLeftCornerRowIndex,
                          int topLeftCornerColumIndex,
                          TrnTetrominoRotationAngle angle);
void trn_piece_destroy();

void trn_piece_move_to_left(TrnPiece* toBeMoved);
void trn_piece_move_to_right(TrnPiece* toBeMoved);
void trn_piece_move_to_bottom(TrnPiece* toBeMoved);
void trn_piece_move_to_top(TrnPiece* toBeMoved);
void trn_piece_rotate_clockwise(TrnPiece* toBeRotated);
void trn_piece_rotate_counter_clockwise(TrnPiece* toBeRotated);
bool trn_piece_equal(TrnPiece const left, TrnPiece const right);
TrnPositionInGrid trn_piece_position_in_grid(TrnPiece* piece, 
                                             int squareIndex);

#endif
