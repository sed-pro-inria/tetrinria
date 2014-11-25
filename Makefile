CFLAGS=-fPIC -Icore -Igtk $(shell pkg-config --cflags gtk+-2.0)
LDLIBS= -L$(abspath core) -ltetrinria_core $(shell pkg-config --libs gtk+-2.0)

LIBTETRINRIA_CORE_OBJECTS=core/color.o core/piece.o core/tetromino.o core/position_in_grid.o core/grid.o core/game.o core/init.o
TETRINRIA_GTK_OBJECTS=gtk/tetrinria-gtk.o gtk/gui.o gtk/window.o

all: core/libtetrinria_core.so gtk/tetrinria-gtk

clean:
	rm -f core/libtetrinria_core.so gtk/tetrinria-gtk $(LIBTETRINRIA_CORE_OBJECTS) $(TETRINRIA_GTK_OBJECTS)

test: core/test_tetrinria
	core/test_tetrinria

core/libtetrinria_core.so: $(LIBTETRINRIA_CORE_OBJECTS)
	gcc -shared -o $@ $?

gtk/tetrinria-gtk: $(TETRINRIA_GTK_OBJECTS)
