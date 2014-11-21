#include "gui.h"

#include <malloc.h>


void fill_cell(cairo_t *cr, RGBColor color, unsigned i, unsigned j)
{
  const int line_width = 2;
  double x = j * NPIXELS + line_width;
  double y = i * NPIXELS + line_width;
  double width = NPIXELS - line_width;
  double height = NPIXELS - line_width;

  cairo_rectangle(cr, x, y, width, height);

  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_fill_preserve(cr);
  cairo_set_line_width(cr, line_width);
  cairo_set_source_rgb(cr, color.red * 0.5, color.green * 0.5, color.blue * 0.5);
  cairo_stroke(cr);
}

gint on_timeout_event(gpointer data)
{
  TetrisGUI* self = (TetrisGUI*)data;
  if (! gameTryToMoveBottom(self->game) )
    gameNewPiece(self->game);
  tetris_window_refresh(self->window);
  g_timeout_add(500,on_timeout_event,(gpointer)self);
  return 0;
}

gboolean on_preview_expose_event(GtkWidget* preview,GdkEventExpose* event, TetrisGUI* gui)
{
  cairo_t* cr = gdk_cairo_create(preview->window);

  size_t rowIndex, columnIndex;

  for ( rowIndex = 0; rowIndex < TETROMINO_NUMBER_OF_SQUARES; ++rowIndex )
  {
    for ( columnIndex = 0; columnIndex < TETROMINO_NUMBER_OF_SQUARES; ++columnIndex)
    {
      fill_cell(cr,WHITE,rowIndex,columnIndex);
    }
  }

  size_t squareIndex;
  PositionInGrid* position = gui->game->piece->tetromino.allRotations[ANGLE_0];
  for (squareIndex=0;squareIndex<TETROMINO_NUMBER_OF_SQUARES;++squareIndex)
  {
    rowIndex = position[squareIndex].rowIndex;
    columnIndex = position[squareIndex].columnIndex;
    fill_cell(cr,gui->game->piece->tetromino.color,rowIndex,columnIndex);
  }

  return TRUE;
}

gboolean on_matrix_expose_event(GtkWidget *matrix,GdkEventExpose *event, TetrisGUI* gui)
{
  cairo_t* cr = gdk_cairo_create(matrix->window);

  Grid* grid = gui->game->grid;
  RGBColor color;

  unsigned int irow, icol;
  for (irow = 0; irow < grid->numberOfRows; irow++) {
    for (icol = 0; icol < grid->numberOfColumns; icol++) {
      PositionInGrid pos;
      pos.rowIndex = irow;
      pos.columnIndex = icol;
      TetrominoType type = tetris_grid_get_cell(grid,pos);
      if (type == TETROMINO_VOID)
          color = WHITE;
      else
          color = gui->game->tetrominosCollection->tetrominos[type].color;
      fill_cell(cr, color, irow, icol);
    }
  }
  cairo_destroy(cr);
  return TRUE;
}

gboolean on_key_press_event(GtkWidget *window,
                            GdkEventKey *event,
                            TetrisGUI* gui)
{

  switch (event->keyval) {
  case GDK_Left:
    gameTryToMoveLeft(gui->game);
    break;
  case GDK_Right:
    gameTryToMoveRight(gui->game);
    break;
  case GDK_Up:
    gameTryToRotateClockwise(gui->game);
    break;
  case GDK_Down:
    if (!gameTryToMoveBottom(gui->game))
      gameNewPiece(gui->game);
    break;
  case GDK_KEY_space:
    while (true) {
        if (! gameTryToMoveBottom(gui->game))
            break;
    }
    gameNewPiece(gui->game);
    break;

    break;
  }

  tetris_window_refresh(gui->window);
  
  return TRUE;
}

gboolean button_newgame_clicked(GtkWidget *widget, TetrisGUI* gui) {
  size_t numberOfRows = gui->game->grid->numberOfRows;
  size_t numberOfColumns = gui->game->grid->numberOfColumns;
  tetris_game_destroy(gui->game);
  gui->game = tetris_game_new(numberOfRows,numberOfColumns);
  return TRUE;
}

gboolean button_pause_clicked(GtkWidget *widget, TetrisGUI* gui) {
  if (gui->game->status == GAME_ON)
    gui->game->status = GAME_PAUSED;
  else if (gui->game->status == GAME_PAUSED)
    gui->game->status = GAME_ON;
  return TRUE;
}

TetrisGUI* tetris_gui_new(size_t numberOfRows, size_t numberOfColumns)
{

  TetrisGUI* gui = (TetrisGUI*)malloc(sizeof(TetrisGUI));

  gui->game = tetris_game_new(numberOfRows,numberOfColumns);

  gui->window = tetris_window_new(numberOfRows,numberOfColumns);
  
  g_signal_connect(gui->window->newGameButton, "clicked", G_CALLBACK(button_newgame_clicked), gui);
  g_signal_connect(gui->window->pauseButton, "clicked", G_CALLBACK(button_pause_clicked), gui);

  tetris_window_show(gui->window);
  g_timeout_add(500,on_timeout_event,(gpointer)gui);

  return gui;
}


void tetris_gui_destroy(TetrisGUI* gui)
{
  tetris_game_destroy(gui->game);
  tetris_window_destroy(gui->window);
  free(gui);
}



