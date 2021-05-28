#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
int ground = 400;
const int H = 12;
const int W = 40;
float offsetX = 0, offsetY = 0;
String TileMap[H] = {
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"B                                      B",
"BBBBBBBBB      BBBBBBBBBBBBBBBBBBBBBBBBB",
};
class PLAYER {
public:
	float dx;
	float dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame; 
	//constructor runs automatically
	PLAYER(Texture& image) { //constructor which takes image
		sprite.setTexture(image); //set the sprite or whatever to the image
		rect = FloatRect(0, 0, 40, 50); //set a rect to equal FloatRect(0, 0, width, height)
		dx = 0; //set this to 0
		dy = 0; //set this to 0
		currentFrame = 0;  // set this 0
	};
	//enter a float in this update function
	void update(float time){
			// set the left coordinate of rectangle to be rect.left = 0 + 0 * (whatever is in this function)
			rect.left = rect.left + dx * time;
			Collision(0);
			if (onGround == false) { //so if this is false which its not we will update the dy to be dy + .0006 * time
				dy = dy + 0.0006 * time; // this launches character in air
				rect.top = rect.top + dy * time; // the result of dy * time plus 0 our top coordinate
				}

			if (rect.top > ground) {
				// if top coordinate bigger than 150
				// it will set a limit to 150
					rect.top = ground;
					dy = 0; //set dy to 0
					onGround = true; // and set on ground to true
				}
			Collision(1);
			currentFrame += 0.005 * time; //current frame which is 0 + 0.005 * time
			if (currentFrame > 6) {
				currentFrame -= 6;
			}
			if (dx > 0)
			{
				sprite.setTextureRect(IntRect(40 * int(currentFrame),0, 40, 60));

			}
			if (dx < 0) {
				sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));

			}

			sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

			dx = 0;
		}
	void Collision(int dir)
	{
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
					if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
					if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}

};

int main()
{
	RenderWindow window(VideoMode(800, 450), "hey");
	Texture t;
	t.loadFromFile("C:\\Users\\Administrator\\source\\repos\\sfml_2\\green.png");
	Sprite s;
	float currentFrame = 0;
	PLAYER player(t);
	Clock clock;
	RectangleShape rectangle(Vector2f(32, 32));
	while (window.isOpen()) {
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); // set microseconds  to time and restart the clock
		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.dx = -0.1;
		
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.dx = 0.1;
		}
		//move x 
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			
			//move y
		if (player.onGround) {
				player.dy = -0.4; //sets y axis to be -0.4
				player.onGround = false; 
			}
		}
		player.update(time);
		window.clear(Color::White);
		for(int i =0; i <H; i++)
			for (int j = 0;j < W; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					rectangle.setFillColor(Color::Magenta);
				}
				
					if (TileMap[i][j] == ' ') {
						continue;

					};
				rectangle.setPosition(j*32 , i*32 );
				window.draw(rectangle);
			}
	

		
		window.draw(player.sprite);
		window.display();
		
	}
	return 0;
}
