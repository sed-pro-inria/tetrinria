#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include <stdbool.h>
#include <stddef.h>

#include "rgb_color.h"
#include "positionInGrid.h"

#define TETROMINO_NUMBER_OF_SQUARES 4
#define TETROMINO_NUMBER_OF_ROTATIONS 4
#define TETROMINO_GRID_SIZE 4

typedef unsigned int TetrominoType;

extern TetrominoType const TETROMINO_VOID;

typedef PositionInGrid TetrominoRotation[TETROMINO_NUMBER_OF_SQUARES];
typedef TetrominoRotation TetrominoAllRotations[TETROMINO_NUMBER_OF_ROTATIONS];

enum TetrominoRotationAngle { ANGLE_0=0, ANGLE_90=1, ANGLE_180=2, ANGLE_270=3 };

typedef struct tetromino 
{
  RGBColor color;
  TetrominoType type;
  TetrominoAllRotations allRotations;
} Tetromino;

typedef struct tetromino_collection
{
    unsigned int numberOfTetrominos;
    Tetromino* tetrominos;
} TetrominosCollection;

Tetromino* tetris_tetromino_new(RGBColor const color, TetrominoType const type);


void tetrominosCollectionDestroy(TetrominosCollection* coll);

#endif
