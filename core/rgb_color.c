#include "rgb_color.h"

#define RGB(R,G,B) {R / 255.0, G / 255.0, B / 255.0}

TrnRGBColor const TRN_WHITE = {1,1,1};
TrnRGBColor const TRN_RED = RGB(0xc0, 0x39, 0x2b);
TrnRGBColor const TRN_GREEN = RGB(0x27, 0xae, 0x60);
TrnRGBColor const TRN_BLUE = RGB(0x29, 0x80, 0xb9);
TrnRGBColor const TRN_YELLOW = RGB(0xf3, 0x9c, 0x12);
TrnRGBColor const TRN_ORANGE = RGB(0xd3, 0x54, 0x00);
TrnRGBColor const TRN_TURQUOISE = RGB(0x1a, 0xbc, 0x9c);
TrnRGBColor const TRN_PURPLE = RGB(0x8e, 0x44, 0xad);
TrnRGBColor const TRN_CYAN = {0,1,1};

bool trn_color_equal(TrnRGBColor const left, TrnRGBColor const right)
{
  return (left.red == right.red) &&
         (left.green == right.green) &&
         (left.blue == right.blue);
}
