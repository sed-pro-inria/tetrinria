#ifndef TRN_COLOR_H
#define TRN_COLOR_H

#include <stdbool.h>

typedef struct {
  float red;
  float green;
  float blue;
} TrnColor;

extern TrnColor const TRN_WHITE;
extern TrnColor const TRN_RED;
extern TrnColor const TRN_GREEN;
extern TrnColor const TRN_BLUE;
extern TrnColor const TRN_YELLOW;
extern TrnColor const TRN_ORANGE;
extern TrnColor const TRN_TURQUOISE;
extern TrnColor const TRN_PURPLE;
extern TrnColor const TRN_CYAN;

bool trn_color_equal(TrnColor const left, TrnColor const right);

#endif
