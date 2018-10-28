#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Reporter.hpp"
#include "Calculator.hpp"
#include "Renderer.hpp"

using namespace std;


void test()
{
	complex<double> z1;
	complex<double> z2;

	// Nadajemy z1 wartoœæ  2.66*e^(1.047i) = 2.66*(cos(1.047) + isin(1.047))
	z1 = polar(2.66, 1.047);
	z2 = polar(6.55, 1.8987);

	cout << "z1: " << z1 << endl;
	cout << "z2: " << z2 << endl;

	cout << "exp(z1): " << exp(z1) << endl;
	cout << "exp(z2): " << exp(z2) << endl;
	cout << endl;
	cout << "sin(z1): " << sin(z1) << endl;
	cout << "sin(z2): " << sin(z2) << endl;
		
	// e^(pi*i) = -1
	cout << endl << "e^(pi*i) = ? " << endl;
	cout << exp(3.14159265358 * complex<double>(0, 1));

	/*
	cout << "z1+z2: " << z1 + z2 << endl;
	cout << "z1*z2: " << z1 * z2 << endl;
	cout << "z1/z2: " << z1 / z2 << endl;
	*/

}


// domyslnie 750, 500
unsigned int WINDOW_WIDTH = 850;
unsigned int WINDOW_HEIGHT = 570;

unsigned int imgWidth;
unsigned int imgHeight;


int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot with SFML", sf::Style::Close);
	
	// domyslnie 600, 400
	imgWidth = 810;
	imgHeight = 540; // == imgWidth * lenght_y / length_x	
	

	Renderer renderer;
	Reporter reporter;

	renderer.SetGenerationRange(-2.0, 1.0, -1.0, 1.0);
	Calculator::SetCalculationPrecision(60);

	reporter.timer.start();	
	
	renderer.GenerateImage(imgWidth, imgHeight);	

	reporter.timer.stop();
	cout << "Image generating time: " << reporter.timer.latestDuration() << endl;
	
	renderer.loadSprite();



	renderer.sprite.setOrigin(imgWidth / 2, imgHeight / 2);
	renderer.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color(144, 144, 144));

		window.draw(renderer.sprite);

		window.display();
	}

	/*
	complex<double> compNumber;

	while (true)
	{
		cout << "Give a complex number: ";
		cin >> compNumber;

		bool res = MandelbrotTest(compNumber);
		if (res)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}

	}
	*/

	return 0;
}