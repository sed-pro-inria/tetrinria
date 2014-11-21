#include "grid.h"
#include <stdlib.h>

Grid* tetris_grid_new(unsigned int numberOfRows, unsigned int numberOfColumns)
{
    /* Allocate grid */
    Grid* grid = (Grid*) malloc(sizeof(Grid));

    /* Set number of rows and columns */
    grid->numberOfRows = numberOfRows;
    grid->numberOfColumns = numberOfColumns;

    /* Allocate a classical C-style 2D array: creates an array of numberOfRows
     * pointers, each one pointing to contiguous memory of the column data. */
    grid->tetrominoTypes = (TetrominoType**)
        malloc(sizeof(TetrominoType*) * numberOfRows);
    unsigned int rowIndex;
    for (rowIndex = 0 ; rowIndex < numberOfRows ; rowIndex++)
    {
        grid->tetrominoTypes[rowIndex] = (TetrominoType*)
            malloc(sizeof(TetrominoType) * numberOfColumns);
    }

    /* clear grid, ie intialize it to TETROMINO_VOID */
    tetris_grid_clear(grid);

    return grid;
}

void tetris_grid_destroy(Grid* grid)
{
    /* Deallocate C-style 2D array */
    unsigned int rowIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows ; rowIndex++)
    {
        free(grid->tetrominoTypes[rowIndex]);
    }
    free(grid->tetrominoTypes);

    /* Deallocate grid */
    free(grid);
}

void tetris_grid_clear(Grid* grid)
{
    unsigned int rowIndex;
    unsigned int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            grid->tetrominoTypes[rowIndex][columnIndex] = TETROMINO_VOID;
        }
    }
}

void tetris_grid_set_cell(Grid* grid, PositionInGrid pos, TetrominoType type)
{
    grid->tetrominoTypes[pos.rowIndex][pos.columnIndex] = type;
}

TetrominoType tetris_grid_get_cell(Grid* grid, PositionInGrid pos)
{
    return grid->tetrominoTypes[pos.rowIndex][pos.columnIndex];
}

void tetris_grid_setCellsWithPiece(Grid* grid, Piece* piece, TetrominoType type)
{
    unsigned squareIndex;
    PositionInGrid pos;

    for (squareIndex = 0 ; 
         squareIndex < TETROMINO_NUMBER_OF_SQUARES ;
         squareIndex++)
    {
        pos = piecePositionInGrid(piece, squareIndex);
        tetris_grid_set_cell(grid, pos, type);
    }
}

bool tetris_grid_cellIsInGrid(Grid* grid, PositionInGrid pos)
{
    return 0 <= pos.rowIndex && pos.rowIndex < grid->numberOfRows &&
           0 <= pos.columnIndex && pos.columnIndex < grid->numberOfColumns;
}

bool tetris_grid_cellIsInGridAndIsVoid(Grid* grid, PositionInGrid pos)
{
    return tetris_grid_cellIsInGrid(grid,pos) && tetris_grid_get_cell(grid, pos) == TETROMINO_VOID;
}

bool tetris_grid_canSetCellsWithPiece(Grid* grid, Piece* piece)
{
    unsigned squareIndex;
    PositionInGrid pos;

    for (squareIndex = 0 ; 
         squareIndex < TETROMINO_NUMBER_OF_SQUARES ;
         squareIndex++)
    {
        pos = piecePositionInGrid(piece, squareIndex);
        if (! tetris_grid_cellIsInGridAndIsVoid(grid,pos) ) return false;
    }

    return true;
}

bool tetris_grid_sameGrids(Grid const * const left, Grid const * const right)
{
    // Compare grid dimensions.
    if (left->numberOfRows != right->numberOfRows)
        return false;
    if (left->numberOfColumns != right->numberOfColumns)
        return false;

    // Compare grid values.
    PositionInGrid pos;
    unsigned int rowIndex;
    unsigned int columnIndex;

    for (rowIndex = 0 ; rowIndex < left->numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < left->numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            if (tetris_grid_get_cell(left, pos) != tetris_grid_get_cell(right,pos)) {
               printf("sameGrid: (%u,%u): %u VS %u\n",pos.rowIndex, pos.columnIndex, tetris_grid_get_cell(left, pos), tetris_grid_get_cell(right,pos));
               return false; 
            }
        }
    }
    return true;
}

void tetris_grid_print(Grid const * const grid)
{
    PositionInGrid pos;
    unsigned int rowIndex;
    unsigned int columnIndex;
    TetrominoType type;

    char* symbols[] = {"I","O","T","S","Z","J","L"};

    // Print top matrix border.
    printf("+");
    for (columnIndex = 1 ; columnIndex < grid->numberOfColumns+1 ; columnIndex++) {
        printf("-");
    }
    printf("+\n");

    // Print left matrix border, matrix type values, matrix right border.
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        printf("|");
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            type = tetris_grid_get_cell(grid, pos);
            if (type == TETROMINO_VOID) {
                printf(" ");
            } else {
                printf(symbols[type]);
            }
        }
        printf("|\n");
    }

    // Print bottom matrix border.
    printf("+");
    for (columnIndex = 1 ; columnIndex < grid->numberOfColumns+1 ; columnIndex++) {
        printf("-");
    }
    printf("+\n");
}

bool tetris_is_last_row_complete(Grid const * const grid)
{
    unsigned int rowIndex;
    unsigned int columnIndex;

    PositionInGrid pos;
    pos.rowIndex = grid->numberOfRows - 1;

    TetrominoType type;

    for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        type = tetris_grid_get_cell(grid, pos);
        if (type == TETROMINO_VOID)
            return false;
    }

    return true;
}
