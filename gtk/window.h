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
} TrnWindow;

TrnWindow* trn_window_new(size_t numberOfRows,size_t numberOfColumns);
void trn_window_destroy(TrnWindow* window);
void trn_window_show(TrnWindow* window);
void trn_window_refresh(TrnWindow* window);
void trn_window_update_score(TrnWindow* window, size_t score);

#endif
