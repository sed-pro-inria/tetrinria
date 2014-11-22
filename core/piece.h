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

TrnPiece* trn_piece_new(TrnTetrominoType const type);

TrnPiece trn_piece_create(TrnTetrominoType const type,
                          int const topLeftCornerRowIndex,
                          int const topLeftCornerColumIndex,
                          TrnTetrominoRotationAngle const angle);
void trn_piece_destroy(TrnPiece* piece);

void trn_piece_move_to_left(TrnPiece * const toBeMoved);

void trn_piece_move_to_right(TrnPiece * const toBeMoved);

void trn_piece_move_to_bottom(TrnPiece * const toBeMoved);

void trn_piece_move_to_top(TrnPiece * const toBeMoved);

void trn_piece_rotate_clockwise(TrnPiece * const toBeRotated);

void trn_piece_rotate_counter_clockwise(TrnPiece * const toBeRotated);

bool trn_piece_equal(TrnPiece const left, TrnPiece const right);

TrnPositionInGrid trn_piece_position_in_grid(TrnPiece const * const piece,
                                             int squareIndex);

#endif
