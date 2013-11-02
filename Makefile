#Compiler to use
CC=g++

SRCDIR = src
BINDIR = bin

#Compiler flags
CFLAGS=-O2 -Ilib -lGL -lGLU -lglut

SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
_OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
OBJS = $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(_OBJS))

all: $(OBJS)
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/phys_eng

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(BINDIR)/phys_eng

clean:
	rm $(BINDIR)/*

install_stuff:
	sudo apt-get install libglu1-mesa-dev
	sudo apt-get install libgl1-mesa-dev
	sudo apt-get install freeglut3
