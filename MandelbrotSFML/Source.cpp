#include <iostream>
#include <cmath>
#include <complex>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Reporter.hpp"

using namespace std;

typedef complex<double> compz;
const compz c_i(0, 1);

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
	cout << exp(3.14159265358 * c_i);

	/*
	cout << "z1+z2: " << z1 + z2 << endl;
	cout << "z1*z2: " << z1 * z2 << endl;
	cout << "z1/z2: " << z1 / z2 << endl;
	*/

}


compz func(compz z, compz P)
{
	return z * z + P;
}

// Function that tests if given complex number P satisfies the
// Mandelbrot Set rule, according to given precision (number of iterations)
bool MandelbrotTest(compz P, int iterations = 50)
{
	compz Z(0, 0);

	for (int i = 0; i < iterations; i++)
	{
		Z = func(Z, P);
	}

	return (abs(Z) <= 2.0);

}

// domyslnie 750, 500
unsigned int WINDOW_WIDTH = 850;
unsigned int WINDOW_HEIGHT = 570;


unsigned int imgWidth;
unsigned int imgHeight;

const double X1 = -2.0;
const double X2 = 1.0;
const double Y1 = -1.0;
const double Y2 = 1.0;


int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot with SFML", sf::Style::Close);

	double length_x = X2 - X1;
	double length_y = Y2 - Y1;

	// domyslnie 600, 400
	imgWidth = 810;
	imgHeight = 540; // == imgWidth * length_y / length_x	

	double precision = length_x / imgWidth; // == length_y / imgHeight
	
	sf::Image img;
	img.create(imgWidth, imgHeight, sf::Color::Yellow);

	Reporter reporter;
	
	reporter.timer.start();

	for (int i = 0; i < imgWidth; i++)
		for (int j = 0; j < imgHeight; j++)
		{
			compz C(X1 + i * precision, Y1 + j * precision);

			if (MandelbrotTest(C, 50))
			{
				img.setPixel(i, j, sf::Color::Green);
			}
			else
			{
				img.setPixel(i, j, sf::Color::Black);
			}

		}
	
	reporter.timer.stop();
	cout << "Image generating time: " << reporter.timer.latestDuration() << endl;
	
	sf::Texture txtr;
	txtr.loadFromImage(img);

	
	sf::Sprite sprite(txtr);
	sprite.setOrigin(imgWidth / 2, imgHeight / 2);
	sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


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

		window.draw(sprite);

		window.display();
	}

	/*
	compz compNumber;

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