#ifndef TRN_APPLICATION_H
#define TRN_APPLICATION_H

#include "game.h"
#include "window.h"


typedef struct
{
  TetrisWindow* window;
  Game* game;
} TetrisGUI;

TetrisGUI* trn_gui_new(size_t numberOfRows, size_t numberOfColumns);
void trn_gui_destroy(TetrisGUI* gui);
gboolean on_key_press_event(GtkWidget *window,
                            GdkEventKey *event,
                            TetrisGUI* gui);
gboolean on_preview_expose_event(GtkWidget *matrix, GdkEventExpose *event, TetrisGUI* gui);
gboolean on_matrix_expose_event(GtkWidget *matrix, GdkEventExpose *event, TetrisGUI* gui);

#endif
