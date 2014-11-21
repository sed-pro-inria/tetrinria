#ifndef TRN_POSITION_IN_GRID_H
#define TRN_POSITION_IN_GRID_H

#include <stdbool.h>
#include <stddef.h>

struct positionInGrid
{
  int rowIndex;
  int columnIndex;
};
typedef struct positionInGrid TrnPositionInGrid;

TrnPositionInGrid* trn_position_in_grid_new(size_t rowIndex, size_t columnIndex);
void trn_position_in_grid_destroy(TrnPositionInGrid* position);

bool trn_position_in_grid_equal(TrnPositionInGrid const left, TrnPositionInGrid const right);

#endif

