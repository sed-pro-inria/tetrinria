#include "gui.h"

#include <malloc.h>


void fill_cell(cairo_t *cr, TrnRGBColor color, unsigned i, unsigned j)
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
  if (! trn_game_try_to_move_bottom(self->game) )
  {
    trn_gui_score_complete_rows(self);
    trn_game_new_piece(self->game);
  }
  trn_window_refresh(self->window);
  g_timeout_add(500,on_timeout_event,(gpointer)self);
  return 0;
}

gboolean on_preview_expose_event(GtkWidget* preview,GdkEventExpose* event, TetrisGUI* gui)
{
  cairo_t* cr = gdk_cairo_create(preview->window);

  size_t rowIndex, columnIndex;

  for ( rowIndex = 0; rowIndex < TRN_TETROMINO_NUMBER_OF_SQUARES; ++rowIndex )
  {
    for ( columnIndex = 0; columnIndex < TRN_TETROMINO_NUMBER_OF_SQUARES; ++columnIndex)
    {
      fill_cell(cr,TRN_WHITE,rowIndex,columnIndex);
    }
  }

  size_t squareIndex;

  TrnPiece* piece = gui->game->piece;

  const TrnTetrominoRotation tetromino_rotation = 
      TRN_ALL_TETROMINO_FOUR_ROTATIONS[piece->type][TRN_ANGLE_0];

  TrnRGBColor color = TRN_ALL_TETROMINO_COLORS[piece->type];

  for (squareIndex=0;squareIndex<TRN_TETROMINO_NUMBER_OF_SQUARES;++squareIndex)
  {
    rowIndex = tetromino_rotation[squareIndex].rowIndex;
    columnIndex = tetromino_rotation[squareIndex].columnIndex;
    fill_cell(cr,color,rowIndex,columnIndex);
  }

  return TRUE;
}

gboolean on_matrix_expose_event(GtkWidget *matrix,GdkEventExpose *event, TetrisGUI* gui)
{
  cairo_t* cr = gdk_cairo_create(matrix->window);

  TrnGrid* grid = gui->game->grid;
  TrnRGBColor color;

  unsigned int irow, icol;
  for (irow = 0; irow < grid->numberOfRows; irow++) {
    for (icol = 0; icol < grid->numberOfColumns; icol++) {
      TrnPositionInGrid pos;
      pos.rowIndex = irow;
      pos.columnIndex = icol;
      TrnTetrominoType type = trn_grid_get_cell(grid,pos);
      if (type == TRN_TETROMINO_VOID)
          color = TRN_WHITE;
      else
          color = TRN_ALL_TETROMINO_COLORS[type];
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
    trn_game_try_to_move_left(gui->game);
    break;
  case GDK_Right:
    trn_game_try_to_move_right(gui->game);
    break;
  case GDK_Up:
    trn_game_try_to_rotate_clockwise(gui->game);
    break;
  case GDK_Down:
    if (!trn_game_try_to_move_bottom(gui->game))
    {
      trn_gui_score_complete_rows(gui);
      trn_game_new_piece(gui->game);
    }
    break;
  case GDK_KEY_space:
    while (true) {
        if (! trn_game_try_to_move_bottom(gui->game))
            break;
    }
    trn_gui_score_complete_rows(gui);
    trn_game_new_piece(gui->game);
    break;

    break;
  }

  trn_window_refresh(gui->window);
  
  return TRUE;
}

gboolean button_newgame_clicked(GtkWidget *widget, TetrisGUI* gui) {
  size_t numberOfRows = gui->game->grid->numberOfRows;
  size_t numberOfColumns = gui->game->grid->numberOfColumns;
  trn_game_destroy(gui->game);
  gui->game = trn_game_new(numberOfRows,numberOfColumns);
  return TRUE;
}

gboolean button_pause_clicked(GtkWidget *widget, TetrisGUI* gui) {
  if (gui->game->status == TRN_GAME_ON)
    gui->game->status = TRN_GAME_PAUSED;
  else if (gui->game->status == TRN_GAME_PAUSED)
    gui->game->status = TRN_GAME_ON;
  return TRUE;
}

TetrisGUI* trn_gui_new(size_t numberOfRows, size_t numberOfColumns)
{

  TetrisGUI* gui = (TetrisGUI*)malloc(sizeof(TetrisGUI));

  gui->game = trn_game_new(numberOfRows,numberOfColumns);

  gui->window = trn_window_new(numberOfRows,numberOfColumns);
  
  g_signal_connect(gui->window->newGameButton, "clicked", G_CALLBACK(button_newgame_clicked), gui);
  g_signal_connect(gui->window->pauseButton, "clicked", G_CALLBACK(button_pause_clicked), gui);

  trn_window_show(gui->window);
  g_timeout_add(500,on_timeout_event,(gpointer)gui);

  return gui;
}

void trn_gui_destroy(TetrisGUI* gui)
{
  trn_game_destroy(gui->game);
  trn_window_destroy(gui->window);
  free(gui);
}


void trn_gui_score_complete_rows(TetrisGUI* gui)
{
  size_t row_index;

  for ( row_index=0; row_index<gui->game->grid->numberOfRows; ++row_index)
  {
    if ( trn_grid_is_row_complete(gui->game->grid, row_index) )
    {
      trn_grid_pop_row_and_make_above_fall(gui->game->grid, row_index);
      ++gui->game->score;
    }
  }
  trn_window_update_score(gui->window, gui->game->score);
}
