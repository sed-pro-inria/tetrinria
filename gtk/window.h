#ifndef TRN_WINDOW_H
#define TRN_WINDOW_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#define NPIXELS 24

typedef struct {
  GtkWidget* base;

  GtkWidget* newGameButton;
  GtkWidget* pauseButton;
  GtkWidget* scoreLabel;
  GtkWidget* verticalBox;
  GtkWidget* horizontalBox;
  GtkWidget* matrix;
  GtkWidget* preview;
} TetrisWindow;

TetrisWindow* trn_window_new(size_t numberOfRows,size_t numberOfColumns);
void trn_window_destroy(TetrisWindow* window);
void trn_window_show(TetrisWindow* window);
void trn_window_refresh(TetrisWindow* window);
void trn_window_update_score(TetrisWindow* window, size_t score);

#endif
