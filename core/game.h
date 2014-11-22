#ifndef TRN_GAME_H
#define TRN_GAME_H

#include "grid.h"
#include "piece.h"

typedef enum { TRN_GAME_ON, TRN_GAME_OVER, TRN_GAME_PAUSED} TrnGameStatus;

typedef struct game {
    TrnGameStatus status;
    TrnGrid* grid;
    TrnPiece* piece;
    size_t score;
} Game;

void trn_game_new_piece(Game* game);
Game* trn_game_new(size_t numberOfRows, size_t numberOfColumns);
void trn_game_destroy(Game* game);

bool trn_game_try_to_move(Game* game,
                          void (*move)(TrnPiece*),
                          void (*unmove)(TrnPiece*));
bool trn_game_try_to_move_right(Game* game);
bool trn_game_try_to_move_left(Game* game);
bool trn_game_try_to_move_bottom(Game* game);
bool trn_game_try_to_rotate_clockwise(Game* game);

#endif
