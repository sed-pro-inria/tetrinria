#ifndef TRN_GAME_H
#define TRN_GAME_H

#include "grid.h"
#include "piece.h"

typedef enum { GAME_ON, GAME_OVER, GAME_PAUSED} GameStatus;

typedef struct game {
    GameStatus status;
    Grid* grid;
    Piece* piece;
    TetrominosCollection* tetrominosCollection;
} Game;

void gameNewPiece(Game* game);
Game* tetris_game_new(size_t numberOfRows, size_t numberOfColumns);
void tetris_game_destroy(Game* game);

bool gameTryToMove(Game* game, void (*move)(Piece*), void (*unmove)(Piece*));
bool gameTryToMoveRight(Game* game);
bool gameTryToMoveLeft(Game* game);
bool gameTryToMoveBottom(Game* game);
bool gameTryToRotateClockwise(Game* game);

#endif
