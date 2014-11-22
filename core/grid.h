#ifndef TRN_GRID_H
#define TRN_GRID_H

#include <stdbool.h>

#include "tetromino.h"
#include "piece.h"

typedef struct grid {
    TrnTetrominoType** tetrominoTypes;
    int numberOfRows;
    int numberOfColumns;
} TrnGrid;

TrnGrid* trn_grid_new(int const numberOfRows, int const numberOfColumns);

void trn_grid_destroy(TrnGrid* grid);

void trn_grid_clear(TrnGrid * const grid);

void trn_grid_set_cell(TrnGrid * const grid,
                       TrnPositionInGrid const pos,
                       TrnTetrominoType const type);

TrnTetrominoType trn_grid_get_cell(TrnGrid const * const grid,
                                   TrnPositionInGrid const pos);

void trn_grid_set_cells_with_piece(TrnGrid * const grid,
                                   TrnPiece const * const piece,
                                   TrnTetrominoType const type);

bool trn_grid_cell_is_in_grid(TrnGrid * const grid,
                              TrnPositionInGrid const pos);

bool trn_grid_cell_is_in_grid_and_is_void(TrnGrid const * const grid,
                                          TrnPositionInGrid const pos);

bool trn_grid_can_set_cells_with_piece(TrnGrid * const grid,
                                       TrnPiece const *  const piece);

bool trn_grid_equal(TrnGrid const * const left, TrnGrid const * const right);

void trn_grid_print(TrnGrid const * const grid);

bool trn_grid_is_row_complete(TrnGrid const * const grid, int const rowIndex);

void trn_grid_copy_row_bellow(TrnGrid * const grid, int const rowIndex);

void trn_grid_pop_row_and_make_above_fall(TrnGrid * const grid,
                                          int const rowIndexToPop);

int trn_grid_pop_first_complete_rows_block();

int tnr_grid_find_last_complete_row_index(TrnGrid const * const grid);

void trn_grid_clear_row(TrnGrid * const grid, int const rowIndex);

#endif
