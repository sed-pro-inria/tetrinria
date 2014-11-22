#include "grid.h"
#include "window.h"

#include <malloc.h>


TrnWindow* trn_window_new(int const numberOfRows, int const numberOfColumns)
{
  TrnWindow* window = (TrnWindow*)malloc(sizeof(TrnWindow));

  window->base = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(window->base), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  window->horizontalBox = gtk_hbox_new(TRUE, 10);
  gtk_container_add(GTK_CONTAINER(window->base), window->horizontalBox);  
  
  window->matrix = gtk_drawing_area_new();
  gtk_widget_set_size_request(window->matrix,
                              numberOfColumns*NPIXELS,
                              numberOfRows*NPIXELS);

  gtk_container_add(GTK_CONTAINER(window->horizontalBox), window->matrix);

  window->verticalBox = gtk_vbox_new(TRUE, 10);
  gtk_container_add(GTK_CONTAINER(window->horizontalBox), window->verticalBox);

  window->newGameButton = gtk_button_new_with_label ("New game");
  gtk_container_add(GTK_CONTAINER(window->verticalBox), window->newGameButton);
 
  window->pauseButton = gtk_button_new_with_label ("Pause");
  gtk_container_add(GTK_CONTAINER(window->verticalBox), window->pauseButton);
 
  window->scoreLabel = gtk_label_new("Score:");
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->scoreLabel);


  window->preview = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->preview);
  gtk_widget_set_size_request(window->preview, 4 * NPIXELS, 4 * NPIXELS);
  
  return window;
}
void trn_window_refresh(TrnWindow const * const window)
{
  gtk_widget_queue_draw(window->base);
}

void trn_window_destroy(TrnWindow* window)
{
    free(window);
}

void trn_window_show(TrnWindow const *  const window)
{
  gtk_widget_show(window->preview);
  gtk_widget_show(window->pauseButton);
  gtk_widget_show(window->newGameButton);
  gtk_widget_show(window->scoreLabel);
  gtk_widget_show(window->horizontalBox);
  gtk_widget_show(window->verticalBox);
  gtk_widget_show(window->matrix);
  gtk_widget_show(window->base);
}

void trn_window_update_score(TrnWindow const * const window, int const score)
{
  char score_text[255];
  sprintf(score_text, "Score: %u", score);
  gtk_label_set_text(GTK_LABEL(window->scoreLabel), score_text);
}

