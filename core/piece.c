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

void pieceMoveToLeft(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex--;
}

void pieceMoveToRight(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.columnIndex++;
}

void pieceMoveToBottom(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex++;
}

void pieceMoveToTop(Piece* toBeMoved)
{
  toBeMoved->topLeftCorner.rowIndex--;
}

void pieceRotateClockwise(Piece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+1) % TETROMINO_NUMBER_OF_ROTATIONS;
}

void pieceRotateCounterClockwise(Piece* toBeRotated)
{
    toBeRotated->angle = (toBeRotated->angle+3) % TETROMINO_NUMBER_OF_ROTATIONS;
}

bool samePieces(Piece const left, Piece const right)
{
  return samePositionsInGrid(left.topLeftCorner,right.topLeftCorner) &&
         left.tetromino.type == right.tetromino.type &&
         (left.angle == right.angle);
}

PositionInGrid piecePositionInGrid(Piece* piece, unsigned int squareIndex)
{
    PositionInGrid pos;
    pos.rowIndex = piece->topLeftCorner.rowIndex + 
       piece->tetromino.allRotations[piece->angle][squareIndex].rowIndex;

    pos.columnIndex = piece->topLeftCorner.columnIndex + 
       piece->tetromino.allRotations[piece->angle][squareIndex].columnIndex;

    return pos;
}

