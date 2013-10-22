
CC=g++
CFLAGS=-O2
SRC=Main.cpp Scene.cpp Sphere.cpp Intersection.cpp
OBJS=$(subst .cpp,.o,$(SRC))

all: $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -o phys_eng

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

run:
	./phys_eng

clean:
	rm phys_eng *.o
