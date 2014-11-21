#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

#include "piece.h"
#include "tetromino_srs.h"
#include "grid.h"
#include "game.h"

static size_t random_row_index;
static size_t const ZERO = 0;

TetrominosCollection* tetrominosCollection;

/* Suite initialization */
int init_suite()
{
   /*random_row_index = rand() % NUMBER_OF_ROWS;*/
   tetrominosCollection = getTetrominosCollectionSRS();
   return 0;
}

/* Suite termination */
int clean_suite()
{
   tetrominosCollectionDestroy(tetrominosCollection);
   return 0;
}

#define ADD_TEST_TO_SUITE(suite,test) \
if ( ( CU_add_test(suite, #test, test) == NULL ) ) { \
    CU_cleanup_registry(); \
    return CU_get_error(); \
}

#define ADD_SUITE_TO_REGISTRY(suite) \
suite = CU_add_suite(#suite, init_suite, clean_suite); \
if ( suite == NULL ) { \
  CU_cleanup_registry(); \
  return CU_get_error(); \
}

//////////////////////////////////////////////////////////////////////////////
// Grid suite tests
//////////////////////////////////////////////////////////////////////////////

void test_grid_new_destroy()
{
    // Create a grid.
    unsigned int numberOfRows = 3;
    unsigned int numberOfColumns = 2;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    // Check that values are initialized to TETROMINO_VOID
    unsigned int rowIndex;
    unsigned int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            CU_ASSERT(grid->tetrominoTypes[rowIndex][columnIndex] == TETROMINO_VOID);
        }
    }

    // Free memory.
    tetris_grid_destroy(grid);
}

void test_grid_set_get_cell()
{
    // Create a 3 rows grid.
    unsigned int numberOfRows = 3;
    unsigned int numberOfColumns = 2;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    unsigned int columnIndex;
    PositionInGrid pos;

    // Set first row.
    pos.rowIndex = 0;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        tetris_grid_set_cell(grid, pos, TETROMINO_SRS_O);
    }

    // Set Third row.
    pos.rowIndex = 2;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        tetris_grid_set_cell(grid, pos, TETROMINO_SRS_I);
    }

    // Check first row.
    pos.rowIndex = 0;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( tetris_grid_get_cell(grid, pos) == TETROMINO_SRS_O);
    }

    // Check second row, it has been initialize to TETROMINO_VOID by grid_new.
    pos.rowIndex = 1;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( tetris_grid_get_cell(grid, pos) == TETROMINO_VOID);
    }

    // Check third row.
    pos.rowIndex = 2;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( tetris_grid_get_cell(grid, pos) == TETROMINO_SRS_I);
    }
}

void testPiecePositionInGrid()
{
    // Create a piece;
    Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];
    Piece piece = {{2,3},TETROMINO_I,ANGLE_90};

    // Expected result
    PositionInGrid expectedPos0 = {2,5};
    PositionInGrid expectedPos1 = {3,5};
    PositionInGrid expectedPos2 = {4,5};
    PositionInGrid expectedPos3 = {5,5};

    // Actual results
    PositionInGrid pos0 = piecePositionInGrid(&piece,0);
    PositionInGrid pos1 = piecePositionInGrid(&piece,1);
    PositionInGrid pos2 = piecePositionInGrid(&piece,2);
    PositionInGrid pos3 = piecePositionInGrid(&piece,3);

    // Check actual results versus expected.
    CU_ASSERT( samePositionsInGrid(pos0, expectedPos0) );
    CU_ASSERT( samePositionsInGrid(pos1, expectedPos1) );
    CU_ASSERT( samePositionsInGrid(pos2, expectedPos2) );
    CU_ASSERT( samePositionsInGrid(pos3, expectedPos3) );
}

void testGridSetCellsWithPiece()
{
    // Create a grid.
    unsigned int numberOfRows = 10;
    unsigned int numberOfColumns = 10;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    // Create a piece;
    Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];
    Piece piece = {{2,3},TETROMINO_I,ANGLE_90};

    tetris_grid_setCellsWithPiece(grid, &piece, piece.tetromino.type);

    // The piece position in grid.
    PositionInGrid pos0 = {2,5};
    PositionInGrid pos1 = {3,5};
    PositionInGrid pos2 = {4,5};
    PositionInGrid pos3 = {5,5};
    PositionInGrid pos;

    TetrominoType type;
    TetrominoType expectedType;

    unsigned int rowIndex;
    unsigned int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            pos.rowIndex = rowIndex;
            pos.columnIndex = columnIndex;
            if (samePositionsInGrid(pos, pos0) ||
                samePositionsInGrid(pos, pos1) ||
                samePositionsInGrid(pos, pos2) ||
                samePositionsInGrid(pos, pos3))
            {
                expectedType = TETROMINO_SRS_I;
            } else {
                expectedType = TETROMINO_VOID;
            }
            type = tetris_grid_get_cell(grid,pos);
            CU_ASSERT_EQUAL(type,expectedType);
        }
    }
}

void TestGridCellIsInGrid()
{
    // Create a grid.
    unsigned int numberOfRows = 2;
    unsigned int numberOfColumns = 3;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    PositionInGrid pos;
    unsigned int rowIndex;
    unsigned int columnIndex;

    // Check position that are in grid
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            CU_ASSERT_TRUE(tetris_grid_cellIsInGrid(grid, pos));
        }
    }

    // Check row out of grid from top.
    pos.rowIndex = -1;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT_FALSE(tetris_grid_cellIsInGrid(grid, pos));
    }

    // Check row out of grid from bottom.
    pos.rowIndex = numberOfRows;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT_FALSE(tetris_grid_cellIsInGrid(grid, pos));
    }

    // Check column out of grid from left.
    pos.columnIndex = -1;
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        CU_ASSERT_FALSE(tetris_grid_cellIsInGrid(grid, pos));
    }

    // Check column out of grid from right.
    pos.columnIndex = numberOfColumns;
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        CU_ASSERT_FALSE(tetris_grid_cellIsInGrid(grid, pos));
    }
}

void TestGridCellIsInGridAndIsVoid()
{
    // Create a grid.
    unsigned int numberOfRows = 2;
    unsigned int numberOfColumns = 3;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    // Grid has been initialize to TETROMINO_VOID, modify one cell type.
    PositionInGrid posNotVoid = {1,2};
    tetris_grid_set_cell(grid, posNotVoid, TETROMINO_SRS_O);

    unsigned int rowIndex;
    unsigned int columnIndex;
    PositionInGrid pos;
    bool isInGridAndIsVoid;

    // Check for cells in grid.
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            isInGridAndIsVoid = tetris_grid_cellIsInGridAndIsVoid(grid,pos);
            if (samePositionsInGrid(pos,posNotVoid)) {
                CU_ASSERT_FALSE(isInGridAndIsVoid);
            } else {
                CU_ASSERT_TRUE(isInGridAndIsVoid);
            }
        }
    }

    // Check for cell NOT in grid.
    pos.rowIndex = 5;
    pos.columnIndex = 5;
    isInGridAndIsVoid = tetris_grid_cellIsInGridAndIsVoid(grid,pos);
    CU_ASSERT_FALSE(isInGridAndIsVoid);
}

void TestGridCanSetCellsWithPiece()
{

    /* Reminder on tetromino_srs_i at ANGLE_0 and ANGLE_90:

    T---+---+---+---+
    |   |   |  9|   |   T: topLeftCorner position in grid
    +---+---+---+---+   0: tetromino cells a ANGLE_0
    | 0 | 0 | 01| 0 |   9: tetromino cells a ANGLE_90
    +---+---+---+---+
    |   |   |  9|   |
    +---+---+---+---+
    |   |   |  9|   |
    +---+---+---+---+
    */

    // Create a grid.
    unsigned int numberOfRows = 10;
    unsigned int numberOfColumns = 10;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

    // For now, the grid has only void cells.

    // Ok, in grid and void.
    Piece piece0 = {{0,0},TETROMINO_I,ANGLE_0};
    CU_ASSERT_TRUE( tetris_grid_canSetCellsWithPiece(grid, &piece0) )

    // Ok, still in grid (in the first row).
    Piece piece1 = {{-1,0},TETROMINO_I,ANGLE_0};
    CU_ASSERT_TRUE( tetris_grid_canSetCellsWithPiece(grid, &piece1) )

    // No more in grid.
    Piece piece2 = {{-2,0},TETROMINO_I,ANGLE_0};
    CU_ASSERT_FALSE( tetris_grid_canSetCellsWithPiece(grid, &piece2) )

    // Ok, in grid and void.
    Piece piece3 = {{5,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( tetris_grid_canSetCellsWithPiece(grid, &piece3) )

    // Ok, still in grid (in the first column).
    Piece piece4 = {{5,-2},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( tetris_grid_canSetCellsWithPiece(grid, &piece4) )

    // No more in grid.
    Piece piece5 = {{5,-3},TETROMINO_I,ANGLE_90};
    CU_ASSERT_FALSE( tetris_grid_canSetCellsWithPiece(grid, &piece5) )

    // Now, fill the last grid row with non-void tetrominos.
    PositionInGrid pos;
    unsigned int columnIndex;
    pos.rowIndex = numberOfRows-1 ;
    for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        tetris_grid_set_cell(grid, pos, TETROMINO_SRS_I);
    }

    // Ok, in grid and void.
    Piece piece6 = {{0,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( tetris_grid_canSetCellsWithPiece(grid, &piece6) )

    // Still in grid and void, just above the non-void row.
    Piece piece7 = {{numberOfRows-5,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_TRUE( tetris_grid_canSetCellsWithPiece(grid, &piece7) )

    // In grid, but last cell of piece overlap a non-void cell of the grid.
    Piece piece8 = {{numberOfRows-4,0},TETROMINO_I,ANGLE_90};
    CU_ASSERT_FALSE( tetris_grid_canSetCellsWithPiece(grid, &piece8) )
}

void test_grid_is_last_row_complete()
{
    // Create a grid.
    unsigned int numberOfRows = 4;
    unsigned int numberOfColumns = 4;
    Grid* grid = tetris_grid_new(numberOfRows, numberOfColumns);

    // Last row is void only.
    CU_ASSERT_FALSE( tetris_is_last_row_complete(grid) );

    // Last row is full.
    PositionInGrid pos;
    unsigned int columnIndex;
    pos.rowIndex = numberOfRows-1 ;
    for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        tetris_grid_set_cell(grid, pos, TETROMINO_SRS_I);
    }
    CU_ASSERT_TRUE( tetris_is_last_row_complete(grid) );

    // Last row is full except last element. 
    pos.rowIndex = numberOfRows-1 ;
    pos.columnIndex = numberOfColumns-1 ;
    tetris_grid_set_cell(grid, pos, TETROMINO_VOID);
    CU_ASSERT_FALSE( tetris_is_last_row_complete(grid) );
}

//////////////////////////////////////////////////////////////////////////////
// Tetrominos suite tests
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Piece suite tests
//////////////////////////////////////////////////////////////////////////////


void testPieceMoveToLeft()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedLeftPiece = {{5,2},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};
  pieceMoveToLeft(&piece);
  
  CU_ASSERT( samePieces(piece,expectedLeftPiece) );
}

void testPieceMoveToRight()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedRightPiece = {{5,3},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,2},TETROMINO_I,ANGLE_0};
  pieceMoveToRight(&piece);
  
  CU_ASSERT( samePieces(piece,expectedRightPiece) );
}

void testPieceMoveToBottom()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedBottomPiece = {{6,3},TETROMINO_I,ANGLE_0};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};
  pieceMoveToBottom(&piece);
  
  CU_ASSERT( samePieces(piece,expectedBottomPiece) );
}

void testPieceRotateClockwise()
{
  Tetromino TETROMINO_I = tetrominosCollection->tetrominos[TETROMINO_SRS_I];

  Piece expectedPiece0 = {{5,3},TETROMINO_I,ANGLE_0};
  Piece expectedPiece90 = {{5,3},TETROMINO_I,ANGLE_90};
  Piece expectedPiece180 = {{5,3},TETROMINO_I,ANGLE_180};
  Piece expectedPiece270 = {{5,3},TETROMINO_I,ANGLE_270};
  
  Piece piece = {{5,3},TETROMINO_I,ANGLE_0};

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece90) );

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece180) );

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece270) );

  pieceRotateClockwise(&piece);
  CU_ASSERT( samePieces(piece,expectedPiece0) );
}


//////////////////////////////////////////////////////////////////////////////
// Game suite tests
//////////////////////////////////////////////////////////////////////////////


void test_game_new_destroy()
{
    // Create a game.
    unsigned int numberOfRows = 3;
    unsigned int numberOfColumns = 2;
    Game* game = tetris_game_new(numberOfRows, numberOfColumns);

    // Destroy the game.
    tetris_game_destroy(game);
}


//////////////////////////////////////////////////////////////////////////////
// Functional suite tests
//////////////////////////////////////////////////////////////////////////////

/*
 * Stack four pieces (0,1,2,3) in left bottom corner of the matrix:
 *
 *  # 3-3 2-2    16 (numberOfRows-4)
 *  #   | |
 *  # 1 3 2 0    17 (numberOfRows-3)
 *  # | | | |
 *  # 1 3 2 0    18 (numberOfRows-2)
 *  # |     |
 *  # 1-1   0-0  19 (numberOfRows-1)
 *  ################
 *    0 1 2 3 4
 *    
 *
 *
 */

void stackSomePieces()
{
    unsigned int numberOfRows = 20;
    unsigned int numberOfColumns = 10;
    unsigned int imove;
    Game* game = tetris_game_new(numberOfRows, numberOfColumns);

    // Piece 0. While the piece is falling:
    // Rotate it 3 times.
    for (imove = 0; imove < 3; imove++) {
        CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
        CU_ASSERT_TRUE( gameTryToRotateClockwise(game) );
    }
    // Move piece to left.
    CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
    CU_ASSERT_TRUE( gameTryToMoveLeft(game) );
    // Reach bottom.
    while (true) {
        if (! gameTryToMoveBottom(game))
            break;
    }
    gameNewPiece(game);
    printf("\n");
    tetris_grid_print(game->grid);

    // Piece 1. While the piece is falling:
    // Rotate it 1 times.
    CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
    CU_ASSERT_TRUE( gameTryToRotateClockwise(game) );
    // Move piece to left.
    for (imove = 0; imove < 4; imove++) {
        CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
        CU_ASSERT_TRUE( gameTryToMoveLeft(game) );
    }
    // Reach bottom.
    while (true) {
        if (! gameTryToMoveBottom(game))
            break;
    }
    gameNewPiece(game);
    printf("\n");
    tetris_grid_print(game->grid);

    // Piece 2. While the piece is falling:
    // Rotate it 1 times.
    CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
    CU_ASSERT_TRUE( gameTryToRotateClockwise(game) );
    // Move piece to left.
    for (imove = 0; imove < 2; imove++) {
        CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
        CU_ASSERT_TRUE( gameTryToMoveLeft(game) );
    }
    // Reach bottom.
    while (true) {
        if (! gameTryToMoveBottom(game))
            break;
    }
    gameNewPiece(game);
    printf("\n");
    tetris_grid_print(game->grid);

    // Piece 3. While the piece is falling:
    // Rotate it 3 times.
    for (imove = 0; imove < 3; imove++) {
        CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
        CU_ASSERT_TRUE( gameTryToRotateClockwise(game) );
    }
    // Move piece to left.
    for (imove = 0; imove < 3; imove++) {
        CU_ASSERT_TRUE( gameTryToMoveBottom(game) );
        CU_ASSERT_TRUE( gameTryToMoveLeft(game) );
    }
    // Reach bottom.
    while (true) {
        if (! gameTryToMoveBottom(game))
            break;
    }

    size_t rowIndex;
    size_t columnIndex;
    PositionInGrid pos;
    Grid* expected_grid = tetris_grid_new(numberOfRows, numberOfColumns);

    // Expected expected_grid type for pieces 0 and 2
    for (rowIndex = numberOfRows-4 ; rowIndex < numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 2 ; columnIndex < 4 ; columnIndex++) {
            pos.columnIndex = columnIndex;
            tetris_grid_set_cell(expected_grid, pos, TETROMINO_SRS_J);
        }
    }

    // Expected expected_grid type for pieces 1 and 3
    for (rowIndex = numberOfRows-4 ; rowIndex < numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < 2 ; columnIndex++) {
            pos.columnIndex = columnIndex;
            tetris_grid_set_cell(expected_grid, pos, TETROMINO_SRS_L);
        }
    }

    CU_ASSERT_TRUE( tetris_grid_sameGrids(game->grid, expected_grid) );

    tetris_game_destroy(game);
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
  CU_pSuite suiteTetromino = NULL;
  CU_pSuite suitePiece = NULL;
  CU_pSuite suitePoint = NULL;
  CU_pSuite Suite_grid = NULL;
  CU_pSuite suiteFunctional = NULL;


   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Create Grid test suite */
   ADD_SUITE_TO_REGISTRY(Suite_grid)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_new_destroy)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_set_get_cell)
   ADD_TEST_TO_SUITE(Suite_grid,testPiecePositionInGrid)
   ADD_TEST_TO_SUITE(Suite_grid,testGridSetCellsWithPiece)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCellIsInGrid)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCellIsInGridAndIsVoid)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCanSetCellsWithPiece)
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_row_to_zero)*/
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_grid_to_zero)*/

   /* Create Tetromino test suite */
   /*ADD_SUITE_TO_REGISTRY(suiteTetromino)*/

   /* Create Piece test suite */
   ADD_SUITE_TO_REGISTRY(suitePiece )
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToLeft)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToRight)
   ADD_TEST_TO_SUITE(suitePiece, testPieceMoveToBottom)
   ADD_TEST_TO_SUITE(suitePiece, testPieceRotateClockwise)

   /* Create functional test suite */
   ADD_SUITE_TO_REGISTRY(suiteFunctional)
   ADD_TEST_TO_SUITE(suiteFunctional, stackSomePieces)

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   unsigned int number_of_tests_failed = CU_get_number_of_tests_failed();
   CU_cleanup_registry();

   return number_of_tests_failed;
}
