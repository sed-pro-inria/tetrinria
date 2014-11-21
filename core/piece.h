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

void pieceMoveToLeft(Piece* toBeMoved);
void pieceMoveToRight(Piece* toBeMoved);
void pieceMoveToBottom(Piece* toBeMoved);
void pieceMoveToTop(Piece* toBeMoved);
void pieceRotateClockwise(Piece* toBeRotated);
void pieceRotateCounterClockwise(Piece* toBeRotated);
bool samePieces(Piece const left, Piece const right);
PositionInGrid piecePositionInGrid(Piece* piece, unsigned int squareIndex);

#endif
