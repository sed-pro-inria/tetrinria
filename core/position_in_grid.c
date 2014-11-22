#include "position_in_grid.h"

bool trn_position_in_grid_equal(TrnPositionInGrid const left, 
                                TrnPositionInGrid const right)
{
  return (left.rowIndex == right.rowIndex) &&
         (left.columnIndex == right.columnIndex);
}

