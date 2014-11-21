#ifndef TRN_POSITION_IN_GRID_H
#define TRN_POSITION_IN_GRID_H

#include <stdbool.h>
#include <stddef.h>

struct positionInGrid
{
  int rowIndex;
  int columnIndex;
};
typedef struct positionInGrid PositionInGrid;

PositionInGrid* tetris_position_in_grid_new(size_t rowIndex, size_t columnIndex);
void tetris_position_in_grid_destroy(PositionInGrid* position);

bool samePositionsInGrid(PositionInGrid const left, PositionInGrid const right);

#endif

