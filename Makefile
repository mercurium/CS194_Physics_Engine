#Compiler to use
CC=g++

SRCDIR = src
BINDIR = bin

#Compiler flags
CFLAGS=-O2 -fopenmp -std=c++11 -msse
IFLAGS=-Ilib
LDFLAGS=-lGLEW -lglut -lGLU -lGL -lX11

#SOURCES = $(shell find $(SRCDIR) -name '*.cpp') #Old find that returns everything in src directory
SOURCES = $(shell find $(SRCDIR) -type f \( -iname '*.cpp' ! -iname 'Main.cpp' ! -iname 'Test.cpp' \)  )
_OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
OBJS = $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(_OBJS))

all: $(OBJS) $(BINDIR)/Main.o
	mkdir -p bin
	python config.py
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/phys_eng $(IFLAGS) $(LDFLAGS)

test: $(OBJS) $(BINDIR)/Test.o
	mkdir -p bin
	python config.py
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/phys_eng $(IFLAGS) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

run:
	$(BINDIR)/phys_eng

clean:
	rm $(BINDIR)/*

install_stuff:
	sudo apt-get install libglu1-mesa-dev libglew-dev
	sudo apt-get install libgl1-mesa-dev
	sudo apt-get install freeglut3
