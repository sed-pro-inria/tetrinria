#include <stdlib.h>

#include "tetromino.h"

TrnTetrominoType const TRN_TETROMINO_VOID = 100;

TrnTetromino* trn_tetromino_new(TrnRGBColor const color, TrnTetrominoType const type)
{
  TrnTetromino* tetromino = (TrnTetromino*)malloc(sizeof(TrnTetromino));
  
  tetromino->color = color;
  tetromino->type = type;

  return tetromino;
}

void tetrominos_collection_destroy(TrnTetrominosCollection* coll)
{
    free(coll->tetrominos);
    free(coll);
}
