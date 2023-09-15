#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>

void BorderControl(const sf::RenderWindow& window);
void Movement();



int SIZE = 50; // 50

int horizontalLine = 600 / SIZE;
int verticalLine = 800 / SIZE;

int vx = SIZE;
int vy = SIZE;

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

void GenerateFood() {
	bool validPosition = false;

	while (!validPosition) {
		food.x = rand() % 15;
		food.y = rand() % 11;

		validPosition = true;
		for (int i = 0; i < num; i++) {
			if (snake[i].x == food.x && snake[i].y == food.y) {
				validPosition = false;
				break;
			}
		}
	}
}
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
	std::cout << verticalLine;
	sf::Clock clock;
	float chrono = 0;
	float delay = 1.1;
	int x = 1;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(802, 670), "Retro Snake", sf::Style::Default, settings);
	sf::Event event;

	sf::RectangleShape snakeblock;
	snakeblock.setSize(sf::Vector2f(SIZE-2, SIZE-2));
	snakeblock.setFillColor(sf::Color::Green);
	snakeblock.setOutlineColor(sf::Color::White);

	sf::RectangleShape grid;
	grid.setSize(sf::Vector2f(vx,vy));
	grid.setFillColor(sf::Color::Black);
	grid.setOutlineThickness(1);
	grid.setOutlineColor(sf::Color::White);

	sf::RectangleShape blockFood;
	blockFood.setSize(sf::Vector2f(SIZE-2, SIZE-2));
	blockFood.setFillColor(sf::Color::Red);

	food.x = rand() % 15;
	food.y = rand() % 11;

	sf::Font font;
	if (!font.loadFromFile("C:\\Users\\paul_\\source\\repos\\Snake\\Snake\\font\\Arial.ttf"))
	{
		std::cout << "eror";
	}
	sf::Text currentScore;
	sf::Text lastScore;

	// select the font
	currentScore.setFont(font); // font is a sf::Font
	lastScore.setFont(font);
	lastScore.setPosition(600, 600);
	// set the string to display
	currentScore.setString("Score: ");
	lastScore.setString("Last score: ");

	// set the character size
	currentScore.setCharacterSize(40); // in pixels, not points!

	// set the color
	currentScore.setFillColor(sf::Color::Blue);
	currentScore.setCharacterSize(50);
	// set the text style
	currentScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
	currentScore.setPosition(10, 600);

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
		currentScore.setString("Score: " + std::to_string(num-3));
		if (chrono > delay)
		{
			chrono = 1;
			GameAction();
		}

		window.clear();
		if ((snake[0].x == food.x) && (snake[0].y == food.y))
		{
			
			GenerateFood();
			num++;
		}
		//std::cout << snake->x << " " << snake->y <<" " << foodPosition.x << " " << foodPosition.y << std::endl;
		Movement();

		window.clear();
		BorderControl(window);

		window.clear();
		for (int i = 0; i < horizontalLine; i++)
		{
			for (int j = 0; j < verticalLine; j++)
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
		for (int i = 1; i < num; i++)
		{
			if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			{
				lastScore.setString("last score: " + std::to_string(num - 3));
				num = 3;
			}
		}
		
		blockFood.setPosition(food.x * SIZE, food.y * SIZE);
		window.draw(blockFood);
		window.draw(currentScore);
		window.draw(lastScore);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != 2)
	{
		direction = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != 1)
	{
		direction = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != 0)
	{
		direction = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != 3)
	{
		direction = 0;
	}
}




