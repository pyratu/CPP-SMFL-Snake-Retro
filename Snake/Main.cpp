#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

void BorderControl(const sf::RenderWindow& window);
void Movement();

int SIZE = 50;
int vx = SIZE * SIZE;
int vy = SIZE * 15;
int horizontalLine = 38;
int verticalLine = 21;
int direction = 2;
int num = 3;

struct Snake
{
	int x, y;
}snake[100];

struct Food
{
	int x, y;
}food;

void GameAction()
{
	for (int i = num; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	
	if (direction == 0)
	{
		snake[0].y += 1;
	}
	else if (direction == 1)
	{
		snake[0].x -= 1;
	}
	else if (direction == 2)
	{
		snake[0].x += 1;
	}
	else if (direction == 3)
	{
		snake[0].y -= 1;
	}
}

int main()
{
	sf::Clock clock;
	float chrono = 0;
	float delay = 1.1;
	int x = 1;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML shapes", sf::Style::Default, settings);
	sf::Event event;

	sf::RectangleShape snakeblock;
	snakeblock.setSize(sf::Vector2f(SIZE, SIZE));
	snakeblock.setFillColor(sf::Color::Green);
	snakeblock.setOutlineColor(sf::Color::White);

	sf::RectangleShape grid;
	grid.setSize(sf::Vector2f(vx,vy));
	grid.setFillColor(sf::Color::Black);
	grid.setOutlineThickness(2);
	grid.setOutlineColor(sf::Color::White);

	sf::RectangleShape blockFood;
	blockFood.setSize(sf::Vector2f(SIZE, SIZE));
	blockFood.setFillColor(sf::Color::Red);

	food.x = rand() % 15;
	food.y = rand() % 11;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		chrono += time;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (chrono > delay)
		{
			chrono = 1;
			GameAction();
		}
		
		window.clear();
		if ((snake[0].x == food.x) && (snake[0].y == food.y))
		{
			num++;
			food.x = rand() % 15;
			food.y = rand() % 11;
		}
		//std::cout << snake->x << " " << snake->y <<" " << foodPosition.x << " " << foodPosition.y << std::endl;
		Movement();

		window.clear();
		BorderControl(window);

		window.clear();
		for (int i = 0; i < verticalLine; i++)
		{
			for (int j = 0; j < horizontalLine; j++)
			{
				grid.setPosition(j * SIZE, i * SIZE);
				window.draw(grid);
			}
		}
		for (int i = 0; i < num; i++)
		{
			snakeblock.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
			window.draw(snakeblock);
		}
		
		blockFood.setPosition(food.x* SIZE, food.y * SIZE);
		window.draw(blockFood);
		window.display();

	}
	
	return 0;
}

void BorderControl(const sf::RenderWindow& window) {

	int leftBorder = 0;
	int rightBorder = 15;
	int bottomBorder = 11;
	int topBorder = 0;

	if (snake->x < leftBorder) {
		snake->x = rightBorder;
	}
	if (snake->x > rightBorder) {
		snake->x = leftBorder;
	}
	if (snake->y > bottomBorder) {
		snake->y = topBorder;
	}
	if (snake->y < topBorder) {
		snake->y = bottomBorder;
	}

	
}

void Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = 0;
	}
}




