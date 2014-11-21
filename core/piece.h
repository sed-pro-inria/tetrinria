#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <stddef.h>
#include <stdbool.h>

#include "tetromino.h"

#include <malloc.h>

#define SPACE_DIMENSION 2

typedef struct piece Piece;
struct piece
{
  PositionInGrid topLeftCorner;
  Tetromino tetromino;
  size_t angle;
};

Piece* tetris_piece_new();
void tetris_piece_destroy();

void trn_piece_move_to_left(Piece* toBeMoved);
void trn_piece_move_to_right(Piece* toBeMoved);
void trn_piece_move_to_bottom(Piece* toBeMoved);
void trn_piece_move_to_top(Piece* toBeMoved);
void trn_piece_rotate_clockwise(Piece* toBeRotated);
void trn_piece_rotate_counter_clockwise(Piece* toBeRotated);
bool trn_piece_equal(Piece const left, Piece const right);
PositionInGrid trn_piece_position_in_grid(Piece* piece, unsigned int squareIndex);

#endif
