#include "food.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <ctime>
#include <iostream>
using namespace std;

food::food(int x , int y){
	pos = Vector2f(600.0f, 600.0f);
	b = RectangleShape(pos);
	score = 0;
	maxX = x;
	maxY = y;
}

void food::movePos(){
	srand(time(NULL));
	int x = (rand() % (maxX/20)) * 20;
	int  y = (rand() % (maxY/20)) * 20;
	cout << "rand x: " << x << " rand y: " << y << endl;
	this->pos = Vector2f(x, y);

	// update score
	score++;
}
