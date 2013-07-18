CC=g++
CFLAGS=-c -Wall
LDFLAGS=-L/usr/X11R6/lib$(LIBSELECT) -lIrrlicht -lGL -lGLU -lXrandr -lXext -lX11
SOURCES=src/Tile.cpp src/Player.cpp src/Level.cpp src/Game.cpp src/Main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=morph

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	    $(CC) $(CFLAGS) $< -o $@
