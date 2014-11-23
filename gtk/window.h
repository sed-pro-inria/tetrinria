#ifndef TRN_WINDOW_H
#define TRN_WINDOW_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#define NPIXELS 24

typedef struct {
  GtkWidget* base;

  GtkWidget* newGameButton;
  GtkWidget* pauseButton;
  GtkWidget* verticalBox;
  GtkWidget* horizontalBox;
  GtkWidget* matrix;
  GtkWidget* preview;
  GtkWidget* levelLabel;
  GtkWidget* levelLinesSeparator;
  GtkWidget* linesLabel;
  GtkWidget* linesScoreSeparator;
  GtkWidget* scoreLabel;
  GtkWidget* scorePreviewSeparator;
} TrnWindow;

TrnWindow* trn_window_new(int const numberOfRows, int const numberOfColumns);
void trn_window_destroy(TrnWindow * window);
void trn_window_show(TrnWindow  const *  const window);
void trn_window_refresh(TrnWindow const * const window);
void trn_window_update_score(TrnWindow const * const window, int const score);
void trn_window_update_level(TrnWindow const * const window, int const level);
void trn_window_update_lines(TrnWindow const * const window, int const lines);

#endif
