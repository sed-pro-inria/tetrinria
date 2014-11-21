#include "positionInGrid.h"

#include <malloc.h>

PositionInGrid* tetris_position_in_grid_new(size_t rowIndex, size_t columnIndex)
{
  PositionInGrid* position = (PositionInGrid*)malloc(sizeof(PositionInGrid));

  position->rowIndex = rowIndex;
  position->columnIndex = columnIndex;

  return position;
}

void tetris_position_in_grid_destroy(PositionInGrid* position)
{
  free(position);
}


bool samePositionsInGrid(PositionInGrid const left, PositionInGrid const right)
{
  return (left.rowIndex == right.rowIndex) &&
         (left.columnIndex == right.columnIndex);
}

