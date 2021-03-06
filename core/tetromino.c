#include <stdlib.h>
#include <string.h>

#include "tetromino.h"

TrnTetrominoFourRotationsArray
  TRN_ALL_TETROMINO_FOUR_ROTATIONS[TRN_NUMBER_OF_TETROMINO] =
{
  { // I
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {0,1}, {1,1}, {2,1}, {3,1} } 
  },

  { // O
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} },
  { {1,0}, {2,0}, {1,1}, {2,1} }
  },

  { // T
  { {0,1}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {1,1}, {1,2}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {2,1} },
  { {0,1}, {1,0}, {1,1}, {2,1} }
  },

  { // S
  { {0,1}, {0,2}, {1,0}, {1,1} },
  { {0,1}, {1,1}, {1,2}, {2,2} },
  { {1,1}, {1,2}, {2,0}, {2,1} },
  { {0,0}, {1,0}, {1,1}, {2,1} }
  },

  { // Z
  { {0,0}, {0,1}, {1,1}, {1,2} },
  { {0,2}, {1,1}, {1,2}, {2,1} },
  { {1,0}, {1,1}, {2,1}, {2,2} },
  { {0,1}, {1,0}, {1,1}, {2,0} }
  },

  { // J
  { {0,0}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {0,2}, {1,1}, {2,1} },
  { {1,0}, {1,1}, {1,2}, {2,2} },
  { {0,1}, {1,1}, {2,0}, {2,1} }
  },

  { // L
  { {0,2}, {1,0}, {1,1}, {1,2} },
  { {0,1}, {1,1}, {2,1}, {2,2} },
  { {1,0}, {1,1}, {1,2}, {2,0} },
  { {0,0}, {0,1}, {1,1}, {2,1} }
  }
};
