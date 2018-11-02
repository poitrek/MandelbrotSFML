#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Reporter.hpp"
#include "Calculator.hpp"
#include "Renderer.hpp"
//#include "consoleUtilities.h"

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
	
	// domyslnie 600, 400
	imgWidth = 750;
	imgHeight = 500; // == imgWidth * lenght_y / length_x	
	

	Renderer renderer;
	Reporter reporter;
	
	// Set tested range of complex plane
	renderer.SetGenerationRange(-2.0, 1.0, -1.0, 1.0);
	
	// Set size of image
	renderer.SetImageSize(imgWidth, imgHeight);
	
	// Set number of maximum iterations per pixel
	Calculator::SetCalculationPrecision(50);


	reporter.ViewGenerationParameters(renderer);

	thread t1(&Renderer::GenerateImage, ref(renderer));	
	thread t2(&Reporter::ViewGenerationState, ref(reporter), ref(renderer));


	reporter.timer.start();
	
	t1.join();
	t2.join();
	//renderer.GenerateImage();

	reporter.timer.stop();

	reporter.GenerationTimeReport();

	renderer.loadSprite();


	
	WINDOW_WIDTH = imgWidth + 10;
	WINDOW_HEIGHT = imgHeight + 10;

	renderer.sprite.setOrigin(imgWidth / 2, imgHeight / 2);
	renderer.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	
	sf::RenderWindow window;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot with SFML", sf::Style::Close);
	
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