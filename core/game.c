#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "tetromino_srs.h"
#include <time.h>

static TetrominoType getRandomTetrominoType(Game* game)
{
#ifdef WITH_MOCK
    static size_t noMoreRandomTetrominoTypeIndex = 0;
    size_t numberOfNoMoreRandomTetrominoType = 2;
    TetrominoType noMoreRandomTetrominoType[2] = 
      {TETROMINO_SRS_J, TETROMINO_SRS_L};

    TetrominoType tetrominoType = 
      noMoreRandomTetrominoType[noMoreRandomTetrominoTypeIndex];
    noMoreRandomTetrominoTypeIndex = (noMoreRandomTetrominoTypeIndex + 1) % 
                                     numberOfNoMoreRandomTetrominoType;
    return tetrominoType;
#else
    return rand() % game->tetrominosCollection->numberOfTetrominos;
#endif
}

void gameNewPiece(Game* game)
{
  if (game->status != GAME_ON)
     return;

  game->piece->topLeftCorner.rowIndex = 0;
  game->piece->topLeftCorner.columnIndex = (game->grid->numberOfColumns - 
                                          TETROMINO_GRID_SIZE)/2;
  game->piece->angle = ANGLE_0;
  
  TetrominoType type = getRandomTetrominoType(game);
  game->piece->tetromino = game->tetrominosCollection->tetrominos[type];
  
  if ( tetris_grid_canSetCellsWithPiece(game->grid,game->piece) )
    tetris_grid_setCellsWithPiece(game->grid, game->piece, game->piece->tetromino.type);
  else
    game->status = GAME_OVER;
}

Game* tetris_game_new(size_t numberOfRows, size_t numberOfColumns)
{
    srand(time(NULL));
    Game* game = (Game*) malloc(sizeof(Game));
    game->status = GAME_ON;
    game->grid = tetris_grid_new(numberOfRows, numberOfColumns);
    game->tetrominosCollection = getTetrominosCollectionSRS();

    // Initialize piece
    game->piece = (Piece*) malloc(sizeof(Piece));
    gameNewPiece(game);

    return game;
}

void tetris_game_destroy(Game* game)
{
    free(game->tetrominosCollection);
    free(game->piece);
    tetris_grid_destroy(game->grid);
    free(game);
}

bool gameTryToMoveRight(Game* game)
{
  return  gameTryToMove(game,pieceMoveToRight,pieceMoveToLeft);
}

bool gameTryToMoveLeft(Game* game)
{
  return gameTryToMove(game,pieceMoveToLeft,pieceMoveToRight);
}

bool gameTryToMoveBottom(Game* game)
{
  return gameTryToMove(game,pieceMoveToBottom,pieceMoveToTop);
}

bool gameTryToRotateClockwise(Game* game)
{
  return gameTryToMove(game,pieceRotateClockwise,pieceRotateCounterClockwise);
}

bool gameTryToMove(Game* game,void (*move)(Piece*),void (*unmove)(Piece*))
{
  if (game->status != GAME_ON)
     return false;

  bool managedToMove = true;

  tetris_grid_setCellsWithPiece(game->grid, 
                        game->piece,
                        TETROMINO_VOID);

  move(game->piece);

  if (! tetris_grid_canSetCellsWithPiece(game->grid, game->piece)) {
      managedToMove = false;
      unmove(game->piece);
  }

  tetris_grid_setCellsWithPiece(game->grid, 
                        game->piece,
                        game->piece->tetromino.type);

  return managedToMove;
}


