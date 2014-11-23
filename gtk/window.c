#include "grid.h"
#include "window.h"

#include <malloc.h>


TrnWindow* trn_window_new(int const numberOfRows, int const numberOfColumns)
{
  TrnWindow* window = (TrnWindow*)malloc(sizeof(TrnWindow));

  window->base = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window->base), 400, 500);
  gtk_window_set_resizable (GTK_WINDOW(window->base), FALSE);
  g_signal_connect(G_OBJECT(window->base), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  window->horizontalBox = gtk_hbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window->base), window->horizontalBox);  
  
  window->matrix = gtk_drawing_area_new();
  gtk_widget_set_size_request(window->matrix,
                              numberOfColumns*NPIXELS,
                              numberOfRows*NPIXELS);

  gtk_container_add(GTK_CONTAINER(window->horizontalBox), window->matrix);

  window->verticalBox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window->horizontalBox), window->verticalBox);

  window->newGameButton = gtk_button_new_with_label ("New game");
  gtk_container_add(GTK_CONTAINER(window->verticalBox), window->newGameButton);
 
  window->pauseButton = gtk_button_new_with_label ("Pause");
  gtk_container_add(GTK_CONTAINER(window->verticalBox), window->pauseButton);

  GtkRequisition req;
  window->levelLabel = gtk_label_new("Level: 0");
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->levelLabel);
  gtk_widget_size_request(window->levelLabel, &req);
  gtk_widget_set_size_request(window->levelLabel, req.width, req.height);
  
  window->levelLinesSeparator = gtk_hseparator_new();
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->levelLinesSeparator);
  
  window->linesLabel = gtk_label_new("Lines: 0");
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->linesLabel);

  window->linesScoreSeparator = gtk_hseparator_new();
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->linesScoreSeparator);
  
  window->scoreLabel = gtk_label_new("Score: 0");
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->scoreLabel);

  PangoFontDescription* p = pango_font_description_from_string("DejaVu Sans Mono 14");
  gtk_widget_modify_font(GTK_WIDGET(window->levelLabel), p);
  gtk_widget_modify_font(GTK_WIDGET(window->linesLabel), p);
  gtk_widget_modify_font(GTK_WIDGET(window->scoreLabel), p);
  
  GdkColor color;
  gdk_color_parse ("red", &color);
  gtk_widget_modify_fg(GTK_WIDGET(window->levelLabel), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(GTK_WIDGET(window->linesLabel), GTK_STATE_NORMAL, &color);
  gtk_widget_modify_fg(GTK_WIDGET(window->scoreLabel), GTK_STATE_NORMAL, &color);
  
  window->scorePreviewSeparator = gtk_hseparator_new();
  gtk_container_add(GTK_CONTAINER (window->verticalBox), window->scorePreviewSeparator);
  
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
  gtk_widget_destroy(window->base);
  free(window);
}

void trn_window_show(TrnWindow const *  const window)
{
  gtk_widget_show(window->preview);
  gtk_widget_show(window->pauseButton);
  gtk_widget_show(window->newGameButton);
  gtk_widget_show(window->levelLabel);
  gtk_widget_show(window->levelLinesSeparator);
  gtk_widget_show(window->linesLabel);
  gtk_widget_show(window->linesScoreSeparator);
  gtk_widget_show(window->scoreLabel);
  gtk_widget_show(window->scorePreviewSeparator);
  gtk_widget_show(window->horizontalBox);
  gtk_widget_show(window->verticalBox);
  gtk_widget_show(window->matrix);
  gtk_widget_show(window->base);
}

void trn_window_update_score(TrnWindow const * const window, int const score)
{
  char text[255];
  sprintf(text, "Score: %u", score);
  gtk_label_set_text(GTK_LABEL(window->scoreLabel), text);
}

void trn_window_update_lines(TrnWindow const * const window, int const lines)
{
  char text[255];
  sprintf(text, "Lines: %u", lines);
  gtk_label_set_text(GTK_LABEL(window->linesLabel), text);
}

void trn_window_update_level(TrnWindow const * const window, int const level)
{
  char text[255];
  sprintf(text, "Level: %u", level);
  gtk_label_set_text(GTK_LABEL(window->levelLabel), text);
}

