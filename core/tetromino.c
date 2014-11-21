#include <stdlib.h>

#include "tetromino.h"

TetrominoType const TETROMINO_VOID = 100;

Tetromino* tetris_tetromino_new(RGBColor const color, TetrominoType const type)
{
  Tetromino* tetromino = (Tetromino*)malloc(sizeof(Tetromino));
  
  tetromino->color = color;
  tetromino->type = type;

  return tetromino;
}

void tetrominosCollectionDestroy(TetrominosCollection* coll)
{
    free(coll->tetrominos);
    free(coll);
}
