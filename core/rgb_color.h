#ifndef TRN_RGB_COLOR_H
#define TRN_RGB_COLOR_H

#include <stdbool.h>

typedef struct {
  float red;
  float green;
  float blue;
} TrnRGBColor;

extern TrnRGBColor const TRN_WHITE;
extern TrnRGBColor const TRN_RED;
extern TrnRGBColor const TRN_GREEN;
extern TrnRGBColor const TRN_BLUE;
extern TrnRGBColor const TRN_YELLOW;
extern TrnRGBColor const TRN_ORANGE;
extern TrnRGBColor const TRN_TURQUOISE;
extern TrnRGBColor const TRN_PURPLE;
extern TrnRGBColor const TRN_CYAN;

bool trn_color_equal(TrnRGBColor const left, TrnRGBColor const right);

#endif
