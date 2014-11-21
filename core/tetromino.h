#ifndef TRN_TRN_TETROMINO_H
#define TRN_TRN_TETROMINO_H

#include <stdbool.h>
#include <stddef.h>

#include "rgb_color.h"
#include "positionInGrid.h"

#define TRN_TETROMINO_NUMBER_OF_SQUARES 4
#define TRN_TETROMINO_NUMBER_OF_ROTATIONS 4
#define TRN_TETROMINO_GRID_SIZE 4

typedef unsigned int TrnTetrominoType;

extern TrnTetrominoType const TRN_TETROMINO_VOID;

typedef TrnPositionInGrid TrnTetrominoRotation[TRN_TETROMINO_NUMBER_OF_SQUARES];
typedef TrnTetrominoRotation TrnTetrominoAllRotations[TRN_TETROMINO_NUMBER_OF_ROTATIONS];

enum TrnTetrominoRotationAngle { TRN_ANGLE_0=0, TRN_ANGLE_90=1, TRN_ANGLE_180=2, TRN_ANGLE_270=3 };

typedef struct tetromino
{
  TrnRGBColor color;
  TrnTetrominoType type;
  TrnTetrominoAllRotations allRotations;
} TrnTetromino;

typedef struct tetromino_collection
{
    unsigned int numberOfTetrominos;
    TrnTetromino* tetrominos;
} TrnTetrominosCollection;

TrnTetromino* trn_tetromino_new(TrnRGBColor const color, TrnTetrominoType const type);


void tetrominos_collection_destroy(TrnTetrominosCollection* coll);

#endif
