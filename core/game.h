#ifndef TRN_GAME_H
#define TRN_GAME_H

#include "grid.h"
#include "piece.h"


typedef enum { TRN_GAME_ON, TRN_GAME_OVER, TRN_GAME_PAUSED} TrnGameStatus;

static int const NINTENDO_SCORING[5] = {0, 40, 100, 300, 1200};

typedef struct {
    TrnGameStatus status;
    TrnGrid* grid;
    TrnPiece* current_piece;
    TrnPiece* next_piece;
    int score;
    int lines_count;
    int level;
    int initial_delay;
} TrnGame;

#define LINES_PER_LEVEL 10

void trn_game_next_piece(TrnGame * const game);

TrnGame* trn_game_new(int const numberOfRows, int const numberOfColumns, int const delay);

void trn_game_destroy(TrnGame * game);

void trn_game_over(TrnGame * const game);

bool trn_game_try_to_move(TrnGame* game,
                          void (*move)(TrnPiece * const),
                          void (*unmove)(TrnPiece * const));

bool trn_game_try_to_move_right(TrnGame * const game);

bool trn_game_try_to_move_left(TrnGame * const game);

bool trn_game_try_to_move_bottom(TrnGame * const game);

bool trn_game_try_to_rotate_clockwise(TrnGame * const game);

void trn_game_update_score(TrnGame* game, int const lines_count);

void trn_game_level_up(TrnGame* game);

int trn_game_delay(TrnGame* game);

void trn_game_check_complete_rows(TrnGame* game);
  
#endif
