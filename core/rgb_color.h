#ifndef TETRIS_RGB_COLOR_H
#define TETRIS_RGB_COLOR_H

#include <stdbool.h>

struct rgbColor {
  float red;
  float green;
  float blue;
};
typedef struct rgbColor RGBColor;

extern RGBColor const WHITE;
extern RGBColor const RED;
extern RGBColor const GREEN;
extern RGBColor const BLUE;
extern RGBColor const YELLOW;
extern RGBColor const ORANGE;
extern RGBColor const TURQUOISE;
extern RGBColor const PURPLE;
extern RGBColor const CYAN;

bool sameColors(RGBColor const left, RGBColor const right);

#endif
