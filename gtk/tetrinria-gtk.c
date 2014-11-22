/* https://developer.gnome.org/gtk2/stable/GtkDrawingArea.html */
#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "rgb_color.h"
#include "tetromino_srs.h"
#include "gui.h"
#include "init.h"

int main(int argc, char* argv[]) 
{
  int const numberOfRows = 20;
  int const numberOfColumns = 10;

  gtk_init(&argc, &argv);
  trn_init();

  TrnGUI* gui = trn_gui_new(numberOfRows,numberOfColumns);
   g_signal_connect(G_OBJECT(gui->window->base), "key_press_event", G_CALLBACK(on_key_press_event), gui);
  g_signal_connect(G_OBJECT(gui->window->matrix), "expose_event", G_CALLBACK(on_matrix_expose_event),gui);
  g_signal_connect(G_OBJECT(gui->window->preview), "expose_event", G_CALLBACK(on_preview_expose_event),gui);

  gtk_main();

  trn_gui_destroy(gui);

  return EXIT_SUCCESS;
}
