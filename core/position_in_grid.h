#ifndef TRN_POSITION_IN_GRID_H
#define TRN_POSITION_IN_GRID_H

#include <stdbool.h>
#include <stddef.h>

typedef struct 
{
  int rowIndex;
  int columnIndex;
} TrnPositionInGrid;

bool trn_position_in_grid_equal(TrnPositionInGrid const left,
                                TrnPositionInGrid const right);

#endif

