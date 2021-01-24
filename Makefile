CXX=g++
SRCS=main.cpp food.h food.cpp 
OBJS=snake
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

main:
	$(CXX) -g -fsanitize=address $(SRCS) -o $(OBJS)  $(LFLAGS)

clean:
	rm -rf $(OBJS)
