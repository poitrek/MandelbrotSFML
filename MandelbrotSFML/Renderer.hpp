#pragma once
#include <SFML/Graphics.hpp>
#include "Calculator.hpp"

class Renderer
{
private:
	double precisionPerPixel;
	double X1, X2, Y1, Y2;
	sf::Image img;
	sf::Texture txtr;

public:
	sf::Sprite sprite;

	void SetGenerationRange(double _X1 = -2.0, double _X2 = 1.0, double _Y1 = -1.0, double _Y2 = 1.0)
	{
		X1 = _X1;
		X2 = _X2;
		Y1 = _Y1;
		Y2 = _Y2;
	}

	void GenerateImage(unsigned int imgWidth, unsigned int imgHeight)
	{
		img.create(imgWidth, imgHeight, sf::Color::Yellow);

		double length_x = X2 - X1;
		double length_y = Y2 - Y1;
		precisionPerPixel = length_x / imgWidth; // == length_y / imgHeight

		// Setting properly all the pixels
		for (unsigned int i = 0; i < imgWidth; i++)
			for (unsigned int j = 0; j < imgHeight; j++)
			{
				complex<double> C(X1 + i * precisionPerPixel, Y1 + j * precisionPerPixel);

				if (Calculator::MandelbrotTest(C))
				{
					img.setPixel(i, j, sf::Color::Green);
				}
				else
				{
					img.setPixel(i, j, sf::Color::Black);
				}

			}
	}

	void loadSprite()
	{
		txtr.loadFromImage(img);

		sprite.setTexture(txtr);
	}
};

