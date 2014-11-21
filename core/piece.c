#include "piece.h"

Piece* tetris_piece_new(TetrominoType const type)
{
  Piece* piece = (Piece*)malloc(sizeof(Piece));

  //piece->topLeftCorner = tetris_position_in_grid_new(0,0);
  //piece->tetromino = tetris_tetromino_new(type);
  //piece->angle = ANGLE_0;
}

void tetris_piece_destroy(Piece* piece)
{
  free(piece);
}

void trn_piece_move_to_left(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex--;
}

void trn_piece_move_to_right(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex++;
}

void trn_piece_move_to_bottom(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex++;
}

void trn_piece_move_to_top(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex--;
}

void trn_piece_rotate_clockwise(Piece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+1) % TETROMINO_NUMBER_OF_ROTATIONS;
}

void trn_piece_rotate_counter_clockwise(Piece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+3) % TETROMINO_NUMBER_OF_ROTATIONS;
}

bool trn_piece_equal(Piece const left, Piece const right)
{
  return samePositionsInGrid(left.topLeftCorner,right.topLeftCorner) &&
         left.tetromino.type == right.tetromino.type &&
         (left.angle == right.angle);
}

PositionInGrid trn_piece_position_in_grid(Piece* piece, unsigned int squareIndex)
{
    PositionInGrid pos;
    pos.rowIndex = piece->topLeftCorner.rowIndex + 
       piece->tetromino.allRotations[piece->angle][squareIndex].rowIndex;

    pos.columnIndex = piece->topLeftCorner.columnIndex + 
       piece->tetromino.allRotations[piece->angle][squareIndex].columnIndex;

    return pos;
}

