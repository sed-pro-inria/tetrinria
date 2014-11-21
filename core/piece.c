#include "piece.h"

TrnPiece* trn_piece_new(TrnTetrominoType const type)
{
  TrnPiece* piece = (TrnPiece*)malloc(sizeof(TrnPiece));

  //piece->topLeftCorner = trn_position_in_grid_new(0,0);
  //piece->tetromino = trn_tetromino_new(type);
  //piece->angle = TRN_ANGLE_0;
}

void trn_piece_destroy(TrnPiece* piece)
{
  free(piece);
}

void trn_piece_move_to_left(TrnPiece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex--;
}

void trn_piece_move_to_right(TrnPiece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex++;
}

void trn_piece_move_to_bottom(TrnPiece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex++;
}

void trn_piece_move_to_top(TrnPiece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex--;
}

void trn_piece_rotate_clockwise(TrnPiece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+1) % TRN_TETROMINO_NUMBER_OF_ROTATIONS;
}

void trn_piece_rotate_counter_clockwise(TrnPiece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+3) % TRN_TETROMINO_NUMBER_OF_ROTATIONS;
}

bool trn_piece_equal(TrnPiece const left, TrnPiece const right)
{
  return trn_position_in_grid_equal(left.topLeftCorner,right.topLeftCorner) &&
         left.tetromino.type == right.tetromino.type &&
         (left.angle == right.angle);
}

TrnPositionInGrid trn_piece_position_in_grid(TrnPiece* piece, unsigned int squareIndex)
{
    TrnPositionInGrid pos;
    pos.rowIndex = piece->topLeftCorner.rowIndex + 
       piece->tetromino.allRotations[piece->angle][squareIndex].rowIndex;

    pos.columnIndex = piece->topLeftCorner.columnIndex + 
       piece->tetromino.allRotations[piece->angle][squareIndex].columnIndex;

    return pos;
}

