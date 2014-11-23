#ifndef TRN_TRN_TETROMINO_H
#define TRN_TRN_TETROMINO_H

#include <stdbool.h>
#include <stddef.h>

#include "rgb_color.h"
#include "position_in_grid.h"

#define TRN_NUMBER_OF_TETROMINO 7
#define TRN_TETROMINO_NUMBER_OF_SQUARES 4
#define TRN_TETROMINO_NUMBER_OF_ROTATIONS 4
#define TRN_TETROMINO_GRID_SIZE 4

typedef enum {TRN_TETROMINO_I, TRN_TETROMINO_O, TRN_TETROMINO_T, 
              TRN_TETROMINO_S, TRN_TETROMINO_Z, TRN_TETROMINO_J,
              TRN_TETROMINO_L, TRN_TETROMINO_VOID} TrnTetrominoType;

typedef enum {TRN_ANGLE_0, TRN_ANGLE_90, TRN_ANGLE_180, TRN_ANGLE_270 }
  TrnTetrominoRotationAngle;

typedef TrnPositionInGrid 
  TrnTetrominoRotationArray[TRN_TETROMINO_NUMBER_OF_SQUARES];

typedef TrnTetrominoRotationArray
  TrnTetrominoFourRotationsArray[TRN_TETROMINO_NUMBER_OF_ROTATIONS];

typedef TrnPositionInGrid* TrnTetrominoRotation;
typedef TrnPositionInGrid** TrnTetrominoFourRotations;

extern TrnColor
  TRN_ALL_TETROMINO_COLORS[TRN_NUMBER_OF_TETROMINO];

extern TrnTetrominoFourRotationsArray
  TRN_ALL_TETROMINO_FOUR_ROTATIONS[TRN_NUMBER_OF_TETROMINO];

#endif
