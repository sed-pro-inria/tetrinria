#include "piece.h"

TrnPiece* trn_piece_new(TrnTetrominoType const type)
{
  TrnPiece* piece = (TrnPiece*) malloc(sizeof(TrnPiece));
  piece->type = type;
  piece->topLeftCorner.rowIndex = 0;
  piece->topLeftCorner.columnIndex = 0;
  piece->angle = TRN_ANGLE_0;
  return piece;
}

TrnPiece trn_piece_create(TrnTetrominoType const type,
                          int const topLeftCornerRowIndex,
                          int const topLeftCornerColumIndex,
                          TrnTetrominoRotationAngle const angle)
{
    TrnPiece piece;
    piece.type = type;
    piece.topLeftCorner.rowIndex = topLeftCornerRowIndex;
    piece.topLeftCorner.columnIndex = topLeftCornerColumIndex;
    piece.angle = angle;
    return piece;
}

void trn_piece_destroy(TrnPiece* piece)
{
  free(piece);
}

void trn_piece_move_to_left(TrnPiece * const toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex--;
}

void trn_piece_move_to_right(TrnPiece * const toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex++;
}

void trn_piece_move_to_bottom(TrnPiece * const toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex++;
}

void trn_piece_move_to_top(TrnPiece * const toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex--;
}

void trn_piece_rotate_clockwise(TrnPiece * const toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+1) % 
      TRN_TETROMINO_NUMBER_OF_ROTATIONS;
}

void trn_piece_rotate_counter_clockwise(TrnPiece * const toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+3) % 
      TRN_TETROMINO_NUMBER_OF_ROTATIONS;
}

bool trn_piece_equal(TrnPiece const left, TrnPiece const right)
{
  return trn_position_in_grid_equal(left.topLeftCorner,right.topLeftCorner) &&
         left.type == right.type &&
         (left.angle == right.angle);
}

TrnPositionInGrid trn_piece_position_in_grid(TrnPiece const * const piece, 
                                             int squareIndex)
{
    const TrnTetrominoRotation rotation = 
        TRN_ALL_TETROMINO_FOUR_ROTATIONS[piece->type][piece->angle];

    const TrnPositionInGrid square = rotation[squareIndex];

    TrnPositionInGrid pos;
    pos.rowIndex = piece->topLeftCorner.rowIndex + square.rowIndex;
    pos.columnIndex = piece->topLeftCorner.columnIndex + square.columnIndex;

    return pos;
}

