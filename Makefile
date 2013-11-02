#Compiler to use
CC=g++

SRCDIR = src
BINDIR = bin

#Compiler flags
CFLAGS=-O2 -Ilib -lGL -lGLU -lglut

_OBJ = Main.o Scene.o Sphere.o Intersection.o
OBJS = $(patsubst %,$(BINDIR)/%,$(_OBJ))

all: $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/phys_eng

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(BINDIR)/phys_eng

clean:
	rm $(BINDIR)/*

install_stuff:
	sudo apt-get install libglu1-mesa-dev
	sudo apt-get install libgl1-mesa-dev
	sudo apt-get install freeglut3
