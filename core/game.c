#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "tetromino_srs.h"
#include <time.h>

static TrnTetrominoType getRandomTrnTetrominoType()
{
#ifdef WITH_MOCK
    static int tetromino_type_index = 0;
    int number_of_tetromino_type = 2;
    TrnTetrominoType mocked_tetromino_type[2] = 
      {TRN_TETROMINO_J, TRN_TETROMINO_L};

    TrnTetrominoType tetrominoType = 
      mocked_tetromino_type[tetromino_type_index];
    tetromino_type_index = (tetromino_type_index + 1) % 
                                     number_of_tetromino_type;
    return tetrominoType;
#else
    return rand() % TRN_NUMBER_OF_TETROMINO;
#endif
}

static bool move_piece_to_column_center(TrnPiece * const piece,
                                        TrnGame const * const game)
{
  int columnIndex = (game->grid->numberOfColumns - 
                     TRN_TETROMINO_GRID_SIZE)/2;

  piece->topLeftCorner.columnIndex = columnIndex;
  bool success = trn_grid_can_set_cells_with_piece(game->grid,game->current_piece);
  trn_grid_fill_piece(game->grid, game->current_piece);
  return success;
}

void trn_game_next_piece(TrnGame * const game)
{
  if (game->status != TRN_GAME_ON)
     return;

  free(game->current_piece);
  game->current_piece = game->next_piece;
  bool success = move_piece_to_column_center(game->current_piece,game);

  game->next_piece = trn_piece_new(getRandomTrnTetrominoType());

  if (!success)
    trn_game_over(game);
}

void trn_game_over(TrnGame * const game) {
    game->status = TRN_GAME_OVER;
    trn_grid_fill(game->grid, TRN_TETROMINO_I);
}

TrnGame* trn_game_new(int const numberOfRows, int const numberOfColumns, int delay)
{
    srand(time(NULL));
    TrnGame* game = (TrnGame*) malloc(sizeof(TrnGame));
    game->status = TRN_GAME_ON;
    game->grid = trn_grid_new(numberOfRows, numberOfColumns);
    game->score = 0;
    game->lines_count = 0;
    game->level = 0;
    game->initial_delay = delay;

    game->current_piece = trn_piece_new(getRandomTrnTetrominoType());
    move_piece_to_column_center(game->current_piece,game);

    game->next_piece = trn_piece_new(getRandomTrnTetrominoType());

    return game;
}

void trn_game_destroy(TrnGame * game)
{
    free(game->current_piece);
    free(game->next_piece);
    trn_grid_destroy(game->grid);
    free(game);
}

bool trn_game_try_to_move_right(TrnGame * const game)
{
  return  trn_game_try_to_move(game,trn_piece_move_to_right, 
                                    trn_piece_move_to_left);
}

bool trn_game_try_to_move_left(TrnGame * const game)
{
  return trn_game_try_to_move(game,trn_piece_move_to_left, 
                                   trn_piece_move_to_right);
}

bool trn_game_try_to_move_down(TrnGame * const game)
{
  bool success = trn_game_try_to_move(game,trn_piece_move_to_bottom,
                                      trn_piece_move_to_top);
  if (!success) {
    trn_game_end_piece(game);
  }
  return success;
}

void trn_game_end_piece(TrnGame * const game)
{
  trn_game_check_complete_rows(game);
  trn_game_next_piece(game);
}

void trn_game_move_to_bottom(TrnGame * const game)
{
  while (true) {
    if (!trn_game_try_to_move_down(game)) {
      break;
    }
  }
}

bool trn_game_try_to_rotate_clockwise(TrnGame * const game)
{
  return trn_game_try_to_move(game,trn_piece_rotate_clockwise,
                                   trn_piece_rotate_counter_clockwise);
}

bool trn_game_try_to_move(TrnGame* game,void (*move)(TrnPiece * const),
                                     void (*unmove)(TrnPiece * const))
{
  if (game->status != TRN_GAME_ON)
     return false;

  bool managedToMove = true;

  trn_grid_remove_piece(game->grid, game->current_piece);
  
  move(game->current_piece);

  if (! trn_grid_can_set_cells_with_piece(game->grid, game->current_piece)) {
      managedToMove = false;
      unmove(game->current_piece);
  }

  trn_grid_fill_piece(game->grid, game->current_piece);

  return managedToMove;
}

void trn_game_check_complete_rows(TrnGame* game)
{
  if (game->status != TRN_GAME_ON)
     return;
  
  int row_index;
  int lines_count = 0;

  for ( row_index=0; row_index<game->grid->numberOfRows; ++row_index)
  {
    if ( trn_grid_is_row_complete(game->grid, row_index) )
    {
      trn_grid_pop_row_and_make_above_fall(game->grid, row_index);
      ++lines_count;
    }
  }
  game->lines_count += lines_count;
  if (game->lines_count > LINES_PER_LEVEL * (game->level+1))
  {
    ++game->level;
  }
}

void trn_game_update_score(TrnGame* game, int const lines_count)
{
  game->score += NINTENDO_SCORING[lines_count] * (game->level+1);
}

void trn_game_level_up(TrnGame* game)
{
  ++game->level;
}

int trn_game_delay(TrnGame* game)
{
  return game->initial_delay * 1./(game->level+1);
}

