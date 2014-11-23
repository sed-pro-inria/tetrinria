#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

#include "piece.h"
#include "tetromino_srs.h"
#include "grid.h"
#include "game.h"
#include "init.h"

/* Suite initialization */
int init_suite()
{
   return 0;
}

/* Suite termination */
int clean_suite()
{
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
// TrnGrid suite tests
//////////////////////////////////////////////////////////////////////////////

void test_grid_new_destroy()
{
    // Create a grid.
    int numberOfRows = 3;
    int numberOfColumns = 2;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    // Check that values are initialized to TRN_TETROMINO_VOID
    int rowIndex;
    int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            CU_ASSERT(grid->tetrominoTypes[rowIndex][columnIndex] == TRN_TETROMINO_VOID);
        }
    }

    // Free memory.
    trn_grid_destroy(grid);
}

void test_grid_set_get_cell()
{
    // Create a 3 rows grid.
    int numberOfRows = 3;
    int numberOfColumns = 2;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    int columnIndex;
    TrnPositionInGrid pos;

    // Set first row.
    pos.rowIndex = 0;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        trn_grid_set_cell(grid, pos, TRN_TETROMINO_O);
    }

    // Set Third row.
    pos.rowIndex = 2;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        trn_grid_set_cell(grid, pos, TRN_TETROMINO_I);
    }

    // Check first row.
    pos.rowIndex = 0;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( trn_grid_get_cell(grid, pos) == TRN_TETROMINO_O);
    }

    // Check second row, it has been initialize to TRN_TETROMINO_VOID by grid_new.
    pos.rowIndex = 1;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( trn_grid_get_cell(grid, pos) == TRN_TETROMINO_VOID);
    }

    // Check third row.
    pos.rowIndex = 2;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT( trn_grid_get_cell(grid, pos) == TRN_TETROMINO_I);
    }
}

void test_piece_position_in_grid()
{
    // Create a piece;
    TrnPiece piece = trn_piece_create(TRN_TETROMINO_I,2,3,TRN_ANGLE_90);

    // Expected result
    TrnPositionInGrid expectedPos0 = {2,5};
    TrnPositionInGrid expectedPos1 = {3,5};
    TrnPositionInGrid expectedPos2 = {4,5};
    TrnPositionInGrid expectedPos3 = {5,5};

    // Actual results
    TrnPositionInGrid pos0 = trn_piece_position_in_grid(&piece,0);
    TrnPositionInGrid pos1 = trn_piece_position_in_grid(&piece,1);
    TrnPositionInGrid pos2 = trn_piece_position_in_grid(&piece,2);
    TrnPositionInGrid pos3 = trn_piece_position_in_grid(&piece,3);

    // Check actual results versus expected.
    CU_ASSERT( trn_position_in_grid_equal(pos0, expectedPos0) );
    CU_ASSERT( trn_position_in_grid_equal(pos1, expectedPos1) );
    CU_ASSERT( trn_position_in_grid_equal(pos2, expectedPos2) );
    CU_ASSERT( trn_position_in_grid_equal(pos3, expectedPos3) );
}

void test_grid_set_cells_with_piece()
{
    // Create a grid.
    int numberOfRows = 10;
    int numberOfColumns = 10;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    // Create a piece;
    TrnPiece piece = trn_piece_create(TRN_TETROMINO_I,2,3,TRN_ANGLE_90);

    trn_grid_set_cells_with_piece(grid, &piece, piece.type);

    // The piece position in grid.
    TrnPositionInGrid pos0 = {2,5};
    TrnPositionInGrid pos1 = {3,5};
    TrnPositionInGrid pos2 = {4,5};
    TrnPositionInGrid pos3 = {5,5};
    TrnPositionInGrid pos;

    TrnTetrominoType type;
    TrnTetrominoType expectedType;

    int rowIndex;
    int columnIndex;
    for (rowIndex = 0 ; rowIndex < grid->numberOfRows; rowIndex++) {
        for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
            pos.rowIndex = rowIndex;
            pos.columnIndex = columnIndex;
            if (trn_position_in_grid_equal(pos, pos0) ||
                trn_position_in_grid_equal(pos, pos1) ||
                trn_position_in_grid_equal(pos, pos2) ||
                trn_position_in_grid_equal(pos, pos3))
            {
                expectedType = TRN_TETROMINO_I;
            } else {
                expectedType = TRN_TETROMINO_VOID;
            }
            type = trn_grid_get_cell(grid,pos);
            CU_ASSERT_EQUAL(type,expectedType);
        }
    }
}

void TestGridCellIsInGrid()
{
    // Create a grid.
    int numberOfRows = 2;
    int numberOfColumns = 3;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    TrnPositionInGrid pos;
    int rowIndex;
    int columnIndex;

    // Check position that are in grid
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            CU_ASSERT_TRUE(trn_grid_cell_is_in_grid(grid, pos));
        }
    }

    // Check row out of grid from top.
    pos.rowIndex = -1;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT_FALSE(trn_grid_cell_is_in_grid(grid, pos));
    }

    // Check row out of grid from bottom.
    pos.rowIndex = numberOfRows;
    for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        CU_ASSERT_FALSE(trn_grid_cell_is_in_grid(grid, pos));
    }

    // Check column out of grid from left.
    pos.columnIndex = -1;
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        CU_ASSERT_FALSE(trn_grid_cell_is_in_grid(grid, pos));
    }

    // Check column out of grid from right.
    pos.columnIndex = numberOfColumns;
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        CU_ASSERT_FALSE(trn_grid_cell_is_in_grid(grid, pos));
    }
}

void TestGridCellIsInGridAndIsVoid()
{
    // Create a grid.
    int numberOfRows = 2;
    int numberOfColumns = 3;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    // TrnGrid has been initialize to TRN_TETROMINO_VOID, modify one cell type.
    TrnPositionInGrid posNotVoid = {1,2};
    trn_grid_set_cell(grid, posNotVoid, TRN_TETROMINO_O);

    int rowIndex;
    int columnIndex;
    TrnPositionInGrid pos;
    bool isInGridAndIsVoid;

    // Check for cells in grid.
    for (rowIndex = 0 ; rowIndex < numberOfRows; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < numberOfColumns ; columnIndex++) {
            pos.columnIndex = columnIndex;
            isInGridAndIsVoid = trn_grid_cell_is_in_grid_and_is_void(grid,pos);
            if (trn_position_in_grid_equal(pos,posNotVoid)) {
                CU_ASSERT_FALSE(isInGridAndIsVoid);
            } else {
                CU_ASSERT_TRUE(isInGridAndIsVoid);
            }
        }
    }

    // Check for cell NOT in grid.
    pos.rowIndex = 5;
    pos.columnIndex = 5;
    isInGridAndIsVoid = trn_grid_cell_is_in_grid_and_is_void(grid,pos);
    CU_ASSERT_FALSE(isInGridAndIsVoid);
}

void TestGridCanSetCellsWithPiece()
{

    /* Reminder on tetromino_srs_i at TRN_ANGLE_0 and TRN_ANGLE_90:

    T---+---+---+---+
    |   |   |  9|   |   T: topLeftCorner position in grid
    +---+---+---+---+   0: tetromino cells a TRN_ANGLE_0
    | 0 | 0 | 01| 0 |   9: tetromino cells a TRN_ANGLE_90
    +---+---+---+---+
    |   |   |  9|   |
    +---+---+---+---+
    |   |   |  9|   |
    +---+---+---+---+
    */

    // Create a grid.
    int numberOfRows = 10;
    int numberOfColumns = 10;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    // For now, the grid has only void cells.

    // Ok, in grid and void.
    TrnPiece piece0 = trn_piece_create(TRN_TETROMINO_I,0,0,TRN_ANGLE_0);
    CU_ASSERT_TRUE( trn_grid_can_set_cells_with_piece(grid, &piece0) )

    // Ok, still in grid (in the first row).
    TrnPiece piece1 = trn_piece_create(TRN_TETROMINO_I,-1,0,TRN_ANGLE_0);
    CU_ASSERT_TRUE( trn_grid_can_set_cells_with_piece(grid, &piece1) )

    // No more in grid.
    TrnPiece piece2 = trn_piece_create(TRN_TETROMINO_I,-2,0,TRN_ANGLE_0);
    CU_ASSERT_FALSE( trn_grid_can_set_cells_with_piece(grid, &piece2) )

    // Ok, in grid and void.
    TrnPiece piece3 = trn_piece_create(TRN_TETROMINO_I,5,0,TRN_ANGLE_90);
    CU_ASSERT_TRUE( trn_grid_can_set_cells_with_piece(grid, &piece3) )

    // Ok, still in grid (in the first column).
    TrnPiece piece4 = trn_piece_create(TRN_TETROMINO_I,5,-2,TRN_ANGLE_90);
    CU_ASSERT_TRUE( trn_grid_can_set_cells_with_piece(grid, &piece4) )

    // No more in grid.
    TrnPiece piece5 = trn_piece_create(TRN_TETROMINO_I,5,-3,TRN_ANGLE_90);
    CU_ASSERT_FALSE( trn_grid_can_set_cells_with_piece(grid, &piece5) )

    // Now, fill the last grid row with non-void tetrominos.
    TrnPositionInGrid pos;
    int columnIndex;
    pos.rowIndex = numberOfRows-1 ;
    for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        trn_grid_set_cell(grid, pos, TRN_TETROMINO_I);
    }

    // Ok, in grid and void.
    TrnPiece piece6 = trn_piece_create(TRN_TETROMINO_I,0,0,TRN_ANGLE_90);
    CU_ASSERT_TRUE( trn_grid_can_set_cells_with_piece(grid, &piece6) )

    // Still in grid and void, just above the non-void row.
    TrnPiece piece7 = trn_piece_create(TRN_TETROMINO_I,numberOfRows-5,0,TRN_ANGLE_90);
    CU_ASSERT_TRUE( trn_grid_can_set_cells_with_piece(grid, &piece7) )

    // In grid, but last cell of piece overlap a non-void cell of the grid.
    TrnPiece piece8 = trn_piece_create(TRN_TETROMINO_I,numberOfRows-4,0,TRN_ANGLE_90);
    CU_ASSERT_FALSE( trn_grid_can_set_cells_with_piece(grid, &piece8) )
}

void test_grid_is_row_complete()
{
    // Create a grid.
    int numberOfRows = 4;
    int numberOfColumns = 4;
    TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);

    // Last row is void only.
    CU_ASSERT_FALSE( trn_grid_is_row_complete(grid,numberOfRows) );

    // Last row is full.
    TrnPositionInGrid pos;
    int columnIndex;
    pos.rowIndex = numberOfRows-1 ;
    for (columnIndex = 0 ; columnIndex < grid->numberOfColumns ; columnIndex++) {
        pos.columnIndex = columnIndex;
        trn_grid_set_cell(grid, pos, TRN_TETROMINO_I);
    }
    CU_ASSERT_TRUE( trn_grid_is_row_complete(grid,numberOfRows) );

    // Last row is full except last element. 
    pos.rowIndex = numberOfRows-1 ;
    pos.columnIndex = numberOfColumns-1 ;
    trn_grid_set_cell(grid, pos, TRN_TETROMINO_VOID);
    CU_ASSERT_FALSE( trn_grid_is_row_complete(grid,numberOfRows) );
}

void test_grid_pop_row_and_make_above_fall()
{
  int numberOfRows = 4;
  int numberOfColumns = 4;

  int rowIndex;
  int columnIndex;
  TrnPositionInGrid pos;

  /* Initial grid
   * +----+
   * |L   |
   * |LL  |
   * |LLL |
   * |LLLL|
   * +----+
   */
  TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);
  for (rowIndex = 0 ; rowIndex < numberOfRows ; rowIndex++) {
      pos.rowIndex = rowIndex;
      for (columnIndex = 0 ; columnIndex <= rowIndex ; columnIndex++) {
          pos.columnIndex = columnIndex;
          trn_grid_set_cell(grid, pos, TRN_TETROMINO_L);
      }
  }

  trn_grid_pop_row_and_make_above_fall(grid, numberOfRows-1);

  /* Expected grid
   * +----+
   * |    |
   * |L   |
   * |LL  |
   * |LLL |
   * +----+
   */
  TrnGrid* expected_grid = trn_grid_new(numberOfRows, numberOfColumns);
  for (rowIndex = 0 ; rowIndex < numberOfRows ; rowIndex++) {
      pos.rowIndex = rowIndex;
      for (columnIndex = 0 ; columnIndex < rowIndex ; columnIndex++) {
          pos.columnIndex = columnIndex;
          trn_grid_set_cell(expected_grid, pos, TRN_TETROMINO_L);
      }
  }

  CU_ASSERT_TRUE( trn_grid_equal(grid, expected_grid) );
}


void test_grid_find_last_complete_row_index()
{
  int numberOfRows = 4;
  int numberOfColumns = 4;

  int rowIndex;
  int columnIndex;
  TrnPositionInGrid pos;

  /* Initial grid
   * +----+
   * |    | 0
   * |LLLL| 1
   * |LLL | 2
   * |LL  | 3
   * +----+
   */
  TrnGrid* grid = trn_grid_new(numberOfRows, numberOfColumns);
  for (rowIndex = 1 ; rowIndex < numberOfRows ; rowIndex++) {
      pos.rowIndex = rowIndex;
      for (columnIndex = 0 ; columnIndex <= numberOfColumns-rowIndex ; columnIndex++) {
          pos.columnIndex = columnIndex;
          trn_grid_set_cell(grid, pos, TRN_TETROMINO_L);
      }
  }

  CU_ASSERT_EQUAL(tnr_grid_find_last_complete_row_index(grid), 1)

  pos.rowIndex = 1;
  pos.columnIndex = 0;
  trn_grid_set_cell(grid, pos, TRN_TETROMINO_VOID);

  CU_ASSERT_EQUAL(tnr_grid_find_last_complete_row_index(grid), -1)
}

//////////////////////////////////////////////////////////////////////////////
// TrnTetrominos suite tests
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// TrnPiece suite tests
//////////////////////////////////////////////////////////////////////////////


void test_piece_move_to_left()
{
  TrnPiece expectedLeftPiece = trn_piece_create(TRN_TETROMINO_I,5,2,TRN_ANGLE_0);
  
  TrnPiece piece = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_0);
  trn_piece_move_to_left(&piece);
  
  CU_ASSERT( trn_piece_equal(piece,expectedLeftPiece) );
}

void test_piece_move_to_right()
{
  TrnPiece expectedRightPiece = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_0);
  
  TrnPiece piece = trn_piece_create(TRN_TETROMINO_I,5,2,TRN_ANGLE_0);
  trn_piece_move_to_right(&piece);
  
  CU_ASSERT( trn_piece_equal(piece,expectedRightPiece) );
}

void test_piece_move_to_bottom()
{
  TrnPiece expectedBottomPiece = trn_piece_create(TRN_TETROMINO_I,6,3,TRN_ANGLE_0);
  
  TrnPiece piece = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_0);
  trn_piece_move_to_bottom(&piece);
  
  CU_ASSERT( trn_piece_equal(piece,expectedBottomPiece) );
}

void test_piece_rotate_clockwise()
{
  TrnPiece expectedPiece0 = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_0);
  TrnPiece expectedPiece90 = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_90);
  TrnPiece expectedPiece180 = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_180);
  TrnPiece expectedPiece270 = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_270);
  
  TrnPiece piece = trn_piece_create(TRN_TETROMINO_I,5,3,TRN_ANGLE_0);

  trn_piece_rotate_clockwise(&piece);
  CU_ASSERT( trn_piece_equal(piece,expectedPiece90) );

  trn_piece_rotate_clockwise(&piece);
  CU_ASSERT( trn_piece_equal(piece,expectedPiece180) );

  trn_piece_rotate_clockwise(&piece);
  CU_ASSERT( trn_piece_equal(piece,expectedPiece270) );

  trn_piece_rotate_clockwise(&piece);
  CU_ASSERT( trn_piece_equal(piece,expectedPiece0) );
}


//////////////////////////////////////////////////////////////////////////////
// Game suite tests
//////////////////////////////////////////////////////////////////////////////


void test_game_new_destroy()
{
    // Create a game.
    int numberOfRows = 3;
    int numberOfColumns = 2;
    int delay = 500;
    TrnGame* game = trn_game_new(numberOfRows, numberOfColumns, delay);

    // Destroy the game.
    trn_game_destroy(game);
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

void stack_some_pieces()
{
    int numberOfRows = 20;
    int numberOfColumns = 10;
    int delay = 500;
    int imove;
    TrnGame* game = trn_game_new(numberOfRows, numberOfColumns, delay);

    // TrnPiece 0. While the piece is falling:
    // Rotate it 3 times.
    for (imove = 0; imove < 3; imove++) {
        CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
        CU_ASSERT_TRUE( trn_game_try_to_rotate_clockwise(game) );
    }
    // Move piece to left.
    CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
    CU_ASSERT_TRUE( trn_game_try_to_move_left(game) );
    // Reach bottom.
    while (true) {
        if (! trn_game_try_to_move_bottom(game))
            break;
    }
    trn_game_next_piece(game);

    // TrnPiece 1. While the piece is falling:
    // Rotate it 1 times.
    CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
    CU_ASSERT_TRUE( trn_game_try_to_rotate_clockwise(game) );
    // Move piece to left.
    for (imove = 0; imove < 4; imove++) {
        CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
        CU_ASSERT_TRUE( trn_game_try_to_move_left(game) );
    }
    // Reach bottom.
    while (true) {
        if (! trn_game_try_to_move_bottom(game))
            break;
    }
    trn_game_next_piece(game);

    // TrnPiece 2. While the piece is falling:
    // Rotate it 1 times.
    CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
    CU_ASSERT_TRUE( trn_game_try_to_rotate_clockwise(game) );
    // Move piece to left.
    for (imove = 0; imove < 2; imove++) {
        CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
        CU_ASSERT_TRUE( trn_game_try_to_move_left(game) );
    }
    // Reach bottom.
    while (true) {
        if (! trn_game_try_to_move_bottom(game))
            break;
    }
    trn_game_next_piece(game);

    // TrnPiece 3. While the piece is falling:
    // Rotate it 3 times.
    for (imove = 0; imove < 3; imove++) {
        CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
        CU_ASSERT_TRUE( trn_game_try_to_rotate_clockwise(game) );
    }
    // Move piece to left.
    for (imove = 0; imove < 3; imove++) {
        CU_ASSERT_TRUE( trn_game_try_to_move_bottom(game) );
        CU_ASSERT_TRUE( trn_game_try_to_move_left(game) );
    }
    // Reach bottom.
    while (true) {
        if (! trn_game_try_to_move_bottom(game))
            break;
    }

    int rowIndex;
    int columnIndex;
    TrnPositionInGrid pos;
    TrnGrid* expected_grid = trn_grid_new(numberOfRows, numberOfColumns);

    // Expected expected_grid type for pieces 0 and 2
    for (rowIndex = numberOfRows-4 ; rowIndex < numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 2 ; columnIndex < 4 ; columnIndex++) {
            pos.columnIndex = columnIndex;
            trn_grid_set_cell(expected_grid, pos, TRN_TETROMINO_J);
        }
    }

    // Expected expected_grid type for pieces 1 and 3
    for (rowIndex = numberOfRows-4 ; rowIndex < numberOfRows ; rowIndex++) {
        pos.rowIndex = rowIndex;
        for (columnIndex = 0 ; columnIndex < 2 ; columnIndex++) {
            pos.columnIndex = columnIndex;
            trn_grid_set_cell(expected_grid, pos, TRN_TETROMINO_L);
        }
    }

    CU_ASSERT_TRUE( trn_grid_equal(game->grid, expected_grid) );

    trn_game_destroy(game);
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
  trn_init();
  CU_pSuite suitePiece = NULL;
  CU_pSuite Suite_grid = NULL;
  CU_pSuite suiteFunctional = NULL;


   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Create TrnGrid test suite */
   ADD_SUITE_TO_REGISTRY(Suite_grid)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_new_destroy)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_set_get_cell)
   ADD_TEST_TO_SUITE(Suite_grid,test_piece_position_in_grid)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_set_cells_with_piece)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCellIsInGrid)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCellIsInGridAndIsVoid)
   ADD_TEST_TO_SUITE(Suite_grid,TestGridCanSetCellsWithPiece)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_pop_row_and_make_above_fall)
   ADD_TEST_TO_SUITE(Suite_grid,test_grid_find_last_complete_row_index)
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_row_to_zero)*/
   /*ADD_TEST_TO_SUITE(Suite_grid,test_set_grid_to_zero)*/

   /* Create TrnPiece test suite */
   ADD_SUITE_TO_REGISTRY(suitePiece )
   ADD_TEST_TO_SUITE(suitePiece, test_piece_move_to_left)
   ADD_TEST_TO_SUITE(suitePiece, test_piece_move_to_right)
   ADD_TEST_TO_SUITE(suitePiece, test_piece_move_to_bottom)
   ADD_TEST_TO_SUITE(suitePiece, test_piece_rotate_clockwise)

   /* Create functional test suite */
   ADD_SUITE_TO_REGISTRY(suiteFunctional)
   ADD_TEST_TO_SUITE(suiteFunctional, stack_some_pieces)

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   int number_of_tests_failed = CU_get_number_of_tests_failed();
   CU_cleanup_registry();

   return number_of_tests_failed;
}
