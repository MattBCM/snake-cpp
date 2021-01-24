#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unistd.h>
#include <vector>
#include <iostream>

//#include "snake.h"
#include "food.h"
using namespace sf;
using namespace std;



class snake{
	public:
		vector<tuple<RectangleShape, float, float>> body;		
		int maxX, maxY;
		char oldDirection = 'u';
		char d = 'u';
		float x=50,  y=500, lastX=0, lastY=0;
		RectangleShape head = RectangleShape(Vector2f(500.0f, 500.0f));			
		RectangleShape tail = RectangleShape(Vector2f(500.0f, 520.0f));		
		RectangleShape tail1= RectangleShape(Vector2f(500.0f, 540.0f));		
		RectangleShape tail2 = RectangleShape(Vector2f(500.0f, 560.0f));		

	public:
		snake(int x, int y){	
			maxX = x;
			maxY = y;
			body.push_back(make_tuple(head, x, y));
			body.push_back(make_tuple(tail, x, y+20));
			body.push_back(make_tuple(tail1, x, y+40));
			body.push_back(make_tuple(tail2, x, y+60));
		}
		void addSquare(){
				RectangleShape last = RectangleShape(Vector2f(lastX, lastY));
				last.setSize(Vector2f(20.0f, 20.0f));
				last.setFillColor(Color::Green);
				body.push_back(make_tuple(last, lastX, lastY));
		}

		void move(){
		
			// Movement
			// TODO: check opposite movement			
			switch(d){
				case 'u':
						if(oldDirection != 'd'){
							if(y<0){
								y = maxY-20;
							}else{
								y -= 20;	
							}
						}else{
							if(y>maxY){
								y = 20;
							}else{
								y += 20;
							}

						}
					break;			
				case 'd':
						if(oldDirection != 'u'){
							if(y>maxY){
								y = 20;
							}else{
								y += 20;
							}
						}else{
							if(y<0){
								y = maxY-20;
							}else{
								y -= 20;	
							}
						}
						break;
				case 'l':
						if(oldDirection != 'r'){
							if(x<0){
								x = maxX - 20;
							}else{
								x -= 20;
							}
						}else{
							if(x>maxX){
								x = 20;
							}else{
								x += 20;
							}
						}
						break;
				case 'r':
						if(oldDirection != 'l'){
							if(x>maxX){
								x = 20;
							}else{
								x += 20;
							}
						}else{
							if(x<0){
								x = maxX - 20;
							}else{
								x -= 20;
							}
						}
						break;
				default:
					break;
			}

					
		
		}



		void update(){
			float oldX = x, oldY = y;

			// head controls
			move();
	

			// update head only
			body[0] = make_tuple(head, x, y);
			get<0>(body[0]).setPosition(x, y);
			get<0>(body[0]).setFillColor(Color::Magenta);


			// update position of the rest of the body
			for(int i=body.size()-1; i>0; i--){
					if(i==1){
						get<0>(body[i]).setPosition(Vector2f(oldX, oldY));
						get<0>(body[i]).setFillColor(Color::Green);
						body[i] = make_tuple(get<0>(body[i]), oldX, oldY);
					}else if(i==body.size()){
						// save last pos for new squares
						lastX = get<1>(body[i]);
						lastY= get<2>(body[i]);

						get<0>(body[i]).setPosition(Vector2f(get<1>(body[i-1]), get<2>(body[i-1])));
						get<0>(body[i]).setFillColor(Color::Green);	
						body[i] = make_tuple(get<0>(body[i]), get<1>(body[i-1]), get<2>(body[i-1]));

					}else{
						get<0>(body[i]).setPosition(Vector2f(get<1>(body[i-1]), get<2>(body[i-1])));
						get<0>(body[i]).setFillColor(Color::Green);	
						body[i] = make_tuple(get<0>(body[i]), get<1>(body[i-1]), get<2>(body[i-1]));

					}
				}

	}
};

bool checkCollisions(snake s, food f){
	return get<0>(s.body[0]).getGlobalBounds().intersects(f.b.getGlobalBounds());
}

bool hasCollidedWithSelf(snake s){
	RectangleShape h = get<0>(s.body[0]);
	for(int i=3; i<s.body.size(); i++){
		RectangleShape c =  get<0>(s.body[i]);
		if(h.getGlobalBounds().intersects(c.getGlobalBounds())) return true;
	}
	return false;
}

int main(){
	// init window
    RenderWindow window(VideoMode(600, 600), "Snake Game");


	// init game objects
	snake s = snake( window.getSize().x, window.getSize().y);
	food f = food( window.getSize().x, window.getSize().y);

	cout << "Window size: "  << window.getSize().x  << "x" << window.getSize().y << endl;
	
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
	

        window.clear(Color(40, 40, 40));


		if(Keyboard::isKeyPressed(Keyboard::W)){	
			s.oldDirection = s.d;
			if(s.oldDirection != 'd'){
				s.d = 'u';
			}
		}
	
		if(Keyboard::isKeyPressed(Keyboard::A)){
			s.oldDirection = s.d;
			if(s.oldDirection != 'r'){
				s.d = 'l';
			}
		}

		if(Keyboard::isKeyPressed(Keyboard::S)){
			s.oldDirection = s.d;
			if(s.oldDirection != 'u'){
				s.d = 'd';
			}
		}

		if(Keyboard::isKeyPressed(Keyboard::D)){	
			s.oldDirection = s.d;
			if(s.oldDirection != 'l'){
				s.d = 'r';
			}
		}

		if(hasCollidedWithSelf(s)){
			f.score = 0;
			s = snake(window.getSize().x, window.getSize().y);	
		}
		s.update();

		// display score
		string score = "Score: " + to_string(f.score);
		Font font = Font();
		font.loadFromFile("RobotoMono-Medium.ttf");
		Text scoreText = Text(score,font, 20 );
		scoreText.setFillColor(Color(251, 241,199));
		scoreText.setPosition(0, 0);


		window.draw(scoreText);

		Vector2f size = Vector2f(20.0f, 20.0f);

		for(int i = 0; i < s.body.size(); i++){
			get<0>(s.body[i]).setSize(size);
   			get<0>(s.body[i]).setFillColor(Color(184,187, 38));
			window.draw(get<0>(s.body[i]));
		}
		
		f.b.setPosition(f.pos);
		f.b.setSize(Vector2f(20, 20));
		f.b.setFillColor(Color(251, 73, 55));

		window.draw(f.b);
		if(checkCollisions(s,  f)){
			f.movePos();
			s.addSquare();	
		}
		usleep(80000);

		

        window.display();
    }

    return 0;
}
