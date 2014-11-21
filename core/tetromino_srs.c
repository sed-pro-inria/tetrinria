#include <stdlib.h>
#include <string.h>

#include "tetromino_srs.h"

static size_t numberOfTetrominosSRS = 7;

static TrnTetrominoAllRotations tetrominoIAllRotations = {
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {0,1}, {1,1}, {2,1}, {3,1} } 
};

static TrnTetrominoAllRotations tetrominoOAllRotations = {
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} }
};

static TrnTetrominoAllRotations tetrominoTAllRotations = {
  { {0,1}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {1,1}, {1,2}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {2,1} },
  { {0,1}, {1,0}, {1,1}, {2,1} }
};

static TrnTetrominoAllRotations tetrominoSAllRotations = {
  { {0,1}, {0,2}, {1,0}, {1,1} },
  { {0,1}, {1,1}, {1,2}, {2,2} },
  { {1,1}, {1,2}, {2,0}, {2,1} },
  { {0,0}, {1,0}, {1,1}, {2,1} }
};

static TrnTetrominoAllRotations tetrominoZAllRotations = {
  { {0,0}, {0,1}, {1,1}, {1,2} },
  { {0,2}, {1,1}, {1,2}, {2,1} },
  { {1,0}, {1,1}, {2,1}, {2,2} },
  { {0,1}, {1,0}, {1,1}, {2,0} }
};

static TrnTetrominoAllRotations tetrominoJAllRotations = {
  { {0,0}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {2,2} },
  { {0,1}, {1,1}, {2,0}, {2,1} }
};

static TrnTetrominoAllRotations tetrominoLAllRotations = {
  { {0,2}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {1,1}, {2,1}, {2,2} },
  { {1,0}, {1,1}, {1,2}, {2,0} },
  { {0,0}, {0,1}, {1,1}, {2,1} }
};

static TrnTetromino tetrominoI;
static TrnTetromino tetrominoO;
static TrnTetromino tetrominoT;
static TrnTetromino tetrominoS;
static TrnTetromino tetrominoZ;
static TrnTetromino tetrominoJ;
static TrnTetromino tetrominoL;

TrnTetrominosCollection* getTetrominosCollectionSRS()
{
    tetrominoI.color = TRN_CYAN;
    tetrominoI.type = TRN_TETROMINO_SRS_I;
    memcpy(tetrominoI.allRotations, tetrominoIAllRotations, sizeof(TrnTetrominoAllRotations));

    tetrominoO.color = TRN_YELLOW;
    tetrominoO.type = TRN_TETROMINO_SRS_O;
    memcpy(tetrominoO.allRotations, tetrominoOAllRotations, sizeof(TrnTetrominoAllRotations));

    tetrominoT.color = TRN_PURPLE;
    tetrominoT.type = TRN_TETROMINO_SRS_T;
    memcpy(tetrominoT.allRotations, tetrominoTAllRotations, sizeof(TrnTetrominoAllRotations));

    tetrominoS.color = TRN_GREEN;
    tetrominoS.type = TRN_TETROMINO_SRS_S;
    memcpy(tetrominoS.allRotations, tetrominoSAllRotations, sizeof(TrnTetrominoAllRotations));

    tetrominoZ.color = TRN_RED;
    tetrominoZ.type = TRN_TETROMINO_SRS_Z;
    memcpy(tetrominoZ.allRotations, tetrominoZAllRotations, sizeof(TrnTetrominoAllRotations));

    tetrominoJ.color = TRN_BLUE;
    tetrominoJ.type = TRN_TETROMINO_SRS_J;
    memcpy(tetrominoJ.allRotations, tetrominoJAllRotations, sizeof(TrnTetrominoAllRotations));

    tetrominoL.color = TRN_ORANGE;
    tetrominoL.type = TRN_TETROMINO_SRS_L;
    memcpy(tetrominoL.allRotations, tetrominoLAllRotations, sizeof(TrnTetrominoAllRotations));

    TrnTetrominosCollection* coll = (TrnTetrominosCollection*) malloc(sizeof(TrnTetrominosCollection));
    coll->numberOfTetrominos = numberOfTetrominosSRS; 
    coll->tetrominos = (TrnTetromino*) malloc(sizeof(TrnTetromino) * numberOfTetrominosSRS);
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_I, &tetrominoI, sizeof(TrnTetromino));
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_O, &tetrominoO, sizeof(TrnTetromino));
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_T, &tetrominoT, sizeof(TrnTetromino));
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_S, &tetrominoS, sizeof(TrnTetromino));
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_Z, &tetrominoZ, sizeof(TrnTetromino));
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_J, &tetrominoJ, sizeof(TrnTetromino));
    memcpy(coll->tetrominos+TRN_TETROMINO_SRS_L, &tetrominoL, sizeof(TrnTetromino));

    return coll;
}
