
#Compiler to use
CC=g++

SRCDIR = src
BINDIR = bin

#Compiler flags
CFLAGS=-O2 -Ilib


# SRC=Main.cpp Scene.cpp Sphere.cpp Intersection.cpp
_OBJ = Main.o Scene.o Sphere.o Intersection.o
OBJS = $(patsubst %,$(BINDIR)/%,$(_OBJ))

all: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/phys_eng

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(BINDIR)/phys_eng

clean:
	rm $(BINDIR)/*
