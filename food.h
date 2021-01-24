#ifndef FOOD_H
#define FOOD_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
using namespace sf;

class food{
	public:
		int score;
		int maxX, maxY;
		RectangleShape b;
		Vector2f pos;
	public:
		food(int x, int y);
		void movePos();
};

#endif
