#pragma once
#include <SFML/Graphics.hpp>
#include "Calculator.hpp"
#include "Reporter.hpp"

class Renderer
{
private:
	double precisionPerPixel;
	double X1, X2, Y1, Y2;
	unsigned int imgWidth, imgHeight;
	unsigned int width_it{ 0 }, height_it{ 0 };
	sf::Image img;
	sf::Texture txtr;

public:
	friend class Reporter;
	//friend void Reporter::ViewGenerationParameters(Renderer &);
	//friend void Reporter::ViewGenerationState(Renderer &);

	Renderer();

	sf::Sprite sprite;

	void SetGenerationRange(double _X1 = -2.0, double _X2 = 1.0, double _Y1 = -1.0, double _Y2 = 1.0)
	{
		X1 = _X1;
		X2 = _X2;
		Y1 = _Y1;
		Y2 = _Y2;
	}

	void SetImageSize(unsigned int _imgWidth, unsigned int _imgHeight)
	{
		imgWidth = _imgWidth;
		imgHeight = _imgHeight;
	}

	void GenerateImage()
	{
		img.create(imgWidth, imgHeight, sf::Color::Yellow);

		double length_x = X2 - X1;
		double length_y = Y2 - Y1;
		precisionPerPixel = length_x / imgWidth; // == length_y / imgHeight

		// Setting properly all the pixels
		for (width_it = 0; width_it < imgWidth; width_it++)
			for (height_it = 0; height_it < imgHeight; height_it++)
			{
				complex<double> C(X1 + width_it * precisionPerPixel, Y1 + height_it * precisionPerPixel);

				if (Calculator::MandelbrotTest(C))
				{
					img.setPixel(width_it, height_it, sf::Color::Green);
				}
				else
				{
					img.setPixel(width_it, height_it, sf::Color::Black);
				}

			}
	}

	void loadSprite()
	{
		txtr.loadFromImage(img);

		sprite.setTexture(txtr);
	}
};

