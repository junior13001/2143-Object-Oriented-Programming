#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <chrono>

struct MineSquare {
	sf::Sprite sprite;
	int bombNeighbors;
	int covered;
};

int main()
{

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span;


	sf::Texture squareTexture;
	if (!squareTexture.loadFromFile("minesweeper/square.png"))
	{
		std::cout << "Could not load square" << std::endl;
	}

	MineSquare** MineWorld;

	MineWorld = new MineSquare*[25];

	for (int i = 0; i < 25; i++) {
		MineWorld[i] = new MineSquare[25];
	}

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			MineWorld[i][j].sprite.setTexture(squareTexture);
			MineWorld[i][j].sprite.setScale(sf::Vector2f(0.1f, 0.1f));
			MineWorld[i][j].sprite.setPosition(sf::Vector2f(i*24, j*24));
		}
	}

	// create the window
	sf::RenderWindow window(sf::VideoMode(600, 600), "My window");


	sf::Sprite sprite;
	sprite.setTexture(squareTexture);
	sprite.setScale(sf::Vector2f(0.1f, 0.1f));
	sprite.setPosition(sf::Vector2f(10, 50));

	sf::Vector2i localPosition;

	bool mouseWasPressed = false;

	window.setKeyRepeatEnabled(false);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// left mouse button is pressed: shoot
			localPosition = sf::Mouse::getPosition(window);
			if (!mouseWasPressed) {
				t1 = std::chrono::high_resolution_clock::now();
				std::cout << localPosition.x << "," << localPosition.y << std::endl;
				mouseWasPressed = true;
				
			}
			
		}
		
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 25; j++) {
				MineWorld[i][j].sprite.setTexture(squareTexture);
				MineWorld[i][j].sprite.setScale(sf::Vector2f(0.1f, 0.1f));
				MineWorld[i][j].sprite.setPosition(sf::Vector2f(i * 24, j * 24));
				window.draw(MineWorld[i][j].sprite);
			}
		}

		t2 = std::chrono::high_resolution_clock::now();
		time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		if (time_span.count() > 0.5 ) {
			mouseWasPressed = false;
		}

		
		// end the current frame
		window.display();
	}

	return 0;
}