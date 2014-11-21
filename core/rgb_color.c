#include "rgb_color.h"

#define RGB(R,G,B) {R / 255.0, G / 255.0, B / 255.0}

RGBColor const WHITE = {1,1,1};
RGBColor const RED = RGB(0xc0, 0x39, 0x2b);
RGBColor const GREEN = RGB(0x27, 0xae, 0x60);
RGBColor const BLUE = RGB(0x29, 0x80, 0xb9);
RGBColor const YELLOW = RGB(0xf3, 0x9c, 0x12);
RGBColor const ORANGE = RGB(0xd3, 0x54, 0x00);
RGBColor const TURQUOISE = RGB(0x1a, 0xbc, 0x9c);
RGBColor const PURPLE = RGB(0x8e, 0x44, 0xad);
RGBColor const CYAN = {0,1,1};

bool sameColors(RGBColor const left, RGBColor const right)
{
  return (left.red == right.red) &&
         (left.green == right.green) &&
         (left.blue == right.blue);
}

