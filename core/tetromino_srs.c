#include <stdlib.h>
#include <string.h>

#include "tetromino_srs.h"

static size_t numberOfTetrominosSRS = 7;

static TetrominoAllRotations tetrominoIAllRotations = {
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {0,1}, {1,1}, {2,1}, {3,1} } 
};

static TetrominoAllRotations tetrominoOAllRotations = {
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} }
};

static TetrominoAllRotations tetrominoTAllRotations = {
  { {0,1}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {1,1}, {1,2}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {2,1} },
  { {0,1}, {1,0}, {1,1}, {2,1} }
};

static TetrominoAllRotations tetrominoSAllRotations = {
  { {0,1}, {0,2}, {1,0}, {1,1} },
  { {0,1}, {1,1}, {1,2}, {2,2} },
  { {1,1}, {1,2}, {2,0}, {2,1} },
  { {0,0}, {1,0}, {1,1}, {2,1} }
};

static TetrominoAllRotations tetrominoZAllRotations = {
  { {0,0}, {0,1}, {1,1}, {1,2} },
  { {0,2}, {1,1}, {1,2}, {2,1} },
  { {1,0}, {1,1}, {2,1}, {2,2} },
  { {0,1}, {1,0}, {1,1}, {2,0} }
};

static TetrominoAllRotations tetrominoJAllRotations = {
  { {0,0}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {2,2} },
  { {0,1}, {1,1}, {2,0}, {2,1} }
};

static TetrominoAllRotations tetrominoLAllRotations = {
  { {0,2}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {1,1}, {2,1}, {2,2} },
  { {1,0}, {1,1}, {1,2}, {2,0} },
  { {0,0}, {0,1}, {1,1}, {2,1} }
};

static Tetromino tetrominoI;
static Tetromino tetrominoO;
static Tetromino tetrominoT;
static Tetromino tetrominoS;
static Tetromino tetrominoZ;
static Tetromino tetrominoJ;
static Tetromino tetrominoL;

TetrominosCollection* getTetrominosCollectionSRS()
{
    tetrominoI.color = CYAN;
    tetrominoI.type = TETROMINO_SRS_I;
    memcpy(tetrominoI.allRotations, tetrominoIAllRotations, sizeof(TetrominoAllRotations));

    tetrominoO.color = YELLOW;
    tetrominoO.type = TETROMINO_SRS_O;
    memcpy(tetrominoO.allRotations, tetrominoOAllRotations, sizeof(TetrominoAllRotations));

    tetrominoT.color = PURPLE;
    tetrominoT.type = TETROMINO_SRS_T;
    memcpy(tetrominoT.allRotations, tetrominoTAllRotations, sizeof(TetrominoAllRotations));

    tetrominoS.color = GREEN;
    tetrominoS.type = TETROMINO_SRS_S;
    memcpy(tetrominoS.allRotations, tetrominoSAllRotations, sizeof(TetrominoAllRotations));

    tetrominoZ.color = RED;
    tetrominoZ.type = TETROMINO_SRS_Z;
    memcpy(tetrominoZ.allRotations, tetrominoZAllRotations, sizeof(TetrominoAllRotations));

    tetrominoJ.color = BLUE;
    tetrominoJ.type = TETROMINO_SRS_J;
    memcpy(tetrominoJ.allRotations, tetrominoJAllRotations, sizeof(TetrominoAllRotations));

    tetrominoL.color = ORANGE;
    tetrominoL.type = TETROMINO_SRS_L;
    memcpy(tetrominoL.allRotations, tetrominoLAllRotations, sizeof(TetrominoAllRotations));

    TetrominosCollection* coll = (TetrominosCollection*) malloc(sizeof(TetrominosCollection));
    coll->numberOfTetrominos = numberOfTetrominosSRS; 
    coll->tetrominos = (Tetromino*) malloc(sizeof(Tetromino) * numberOfTetrominosSRS);
    memcpy(coll->tetrominos+TETROMINO_SRS_I, &tetrominoI, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_O, &tetrominoO, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_T, &tetrominoT, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_S, &tetrominoS, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_Z, &tetrominoZ, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_J, &tetrominoJ, sizeof(Tetromino));
    memcpy(coll->tetrominos+TETROMINO_SRS_L, &tetrominoL, sizeof(Tetromino));

    return coll;
}
