#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "tetromino_srs.h"
#include <time.h>

static TrnTetrominoType getRandomTrnTetrominoType(Game* game)
{
    static int tetromino_type_index = 0;
    int number_of_tetromino_type = 2;
    TrnTetrominoType mocked_tetromino_type[2] = 
      {TRN_TETROMINO_J, TRN_TETROMINO_L};

    TrnTetrominoType tetrominoType = 
      mocked_tetromino_type[tetromino_type_index];
    tetromino_type_index = (tetromino_type_index + 1) % 
                                     number_of_tetromino_type;
    return tetrominoType;
}

static TrnTetrominoType mockGetRandomTrnTetrominoType()
{
    return rand() % TRN_NUMBER_OF_TETROMINO;
}

void trn_game_new_piece(Game* game)
{
  if (game->status != TRN_GAME_ON)
     return;

  game->piece->topLeftCorner.rowIndex = 0;
  game->piece->topLeftCorner.columnIndex = (game->grid->numberOfColumns - 
                                          TRN_TETROMINO_GRID_SIZE)/2;
  game->piece->angle = TRN_ANGLE_0;
  
#ifdef WITH_MOCK
  game->piece->type = getRandomTrnTetrominoType(game);
#else
  game->piece->type = mockGetRandomTrnTetrominoType();
#endif
  
  if ( trn_grid_can_set_cells_with_piece(game->grid,game->piece) )
    trn_grid_set_cells_with_piece(game->grid, 
                                  game->piece,
                                  game->piece->type);
  else
    game->status = TRN_GAME_OVER;
}

Game* trn_game_new(int numberOfRows, int numberOfColumns)
{
    srand(time(NULL));
    Game* game = (Game*) malloc(sizeof(Game));
    game->status = TRN_GAME_ON;
    game->grid = trn_grid_new(numberOfRows, numberOfColumns);
    game->score = 0;

    // Initialize piece
    game->piece = (TrnPiece*) malloc(sizeof(TrnPiece));
    trn_game_new_piece(game);

    return game;
}

void trn_game_destroy(Game* game)
{
    free(game->piece);
    trn_grid_destroy(game->grid);
    free(game);
}

bool trn_game_try_to_move_right(Game* game)
{
  return  trn_game_try_to_move(game,trn_piece_move_to_right, 
                                    trn_piece_move_to_left);
}

bool trn_game_try_to_move_left(Game* game)
{
  return trn_game_try_to_move(game,trn_piece_move_to_left, 
                                   trn_piece_move_to_right);
}

bool trn_game_try_to_move_bottom(Game* game)
{
  return trn_game_try_to_move(game,trn_piece_move_to_bottom,
                                   trn_piece_move_to_top);
}

bool trn_game_try_to_rotate_clockwise(Game* game)
{
  return trn_game_try_to_move(game,trn_piece_rotate_clockwise,
                                   trn_piece_rotate_counter_clockwise);
}

bool trn_game_try_to_move(Game* game,void (*move)(TrnPiece*),
                                     void (*unmove)(TrnPiece*))
{
  if (game->status != TRN_GAME_ON)
     return false;

  bool managedToMove = true;

  trn_grid_set_cells_with_piece(game->grid, 
                        game->piece,
                        TRN_TETROMINO_VOID);

  move(game->piece);

  if (! trn_grid_can_set_cells_with_piece(game->grid, game->piece)) {
      managedToMove = false;
      unmove(game->piece);
  }

  trn_grid_set_cells_with_piece(game->grid, 
                        game->piece,
                        game->piece->type);

  return managedToMove;
}


