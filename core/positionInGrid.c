#include "positionInGrid.h"

#include <malloc.h>

TrnPositionInGrid* trn_position_in_grid_new(size_t rowIndex, size_t columnIndex)
{
  TrnPositionInGrid* position = (TrnPositionInGrid*)malloc(sizeof(TrnPositionInGrid));

  position->rowIndex = rowIndex;
  position->columnIndex = columnIndex;

  return position;
}

void trn_position_in_grid_destroy(TrnPositionInGrid* position)
{
  free(position);
}


bool trn_position_in_grid_equal(TrnPositionInGrid const left, TrnPositionInGrid const right)
{
  return (left.rowIndex == right.rowIndex) &&
         (left.columnIndex == right.columnIndex);
}

