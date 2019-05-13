#include "Renderer.hpp"

Renderer::Renderer()
{
	X1 = -2.0;
	X2 = 1.0;
	Y1 = -1.0;
	Y2 = 1.0;
}

void Renderer::GenerateImage()
{
	img.create(imgWidth, imgHeight, sf::Color::Yellow);

	double length_x = X2 - X1;
	double length_y = Y2 - Y1;
	precisionPerPixel = length_x / imgWidth; // == length_y / imgHeight
	
	int maximumIt = Calculator::GetCalculationPrecision();
	// Setting properly all the pixels
	for (width_it = 0; width_it < imgWidth; width_it++)
		for (height_it = 0; height_it < imgHeight; height_it++)
		{			
			complex<double> C(X1 + width_it * precisionPerPixel, Y1 + height_it * precisionPerPixel);
			
			int N = Calculator::MandelbrotTest(C);

			sf::Color pixelColor;

			
			float ratio = (float)N / (float)maximumIt;
			pixelColor = sf::Color(colorPicker.RedSaturation(ratio),
				colorPicker.GreenSaturation(ratio),
				colorPicker.BlueSaturation(ratio));
			

			/*
			// The number (pixel) is inside of the Mandelbrot set
			if (N == maximumIt)
			{
				pixelColor = sf::Color::Black;
			}
			else
			{
				float SaturationValue = N * (float)255 / (float)maximumIt;
				
				pixelColor = sf::Color(sf::Uint8((SaturationValue)), sf::Uint8(SaturationValue),
					sf::Uint8(SaturationValue / 2));
			}			
			*/

			img.setPixel(width_it, height_it, pixelColor);
			/*
			if (Calculator::MandelbrotTest(C))
			{
				img.setPixel(width_it, height_it, sf::Color::Green);
			}
			else
			{
				img.setPixel(width_it, height_it, sf::Color::Black);
			}
			*/
		}
}

int Renderer::ColorPicker::RedSaturation(float x)
{
	if (x == 1)	return 0;

	if (x >= 0.8)
	{
		return 0;
	}
	else
	{
		float R = 255 * sqrt(0.8 - x);
		return static_cast<int>(R);
	}
}

int Renderer::ColorPicker::GreenSaturation(float x)
{
	if (x == 1)	return 0;

	if (x <= 0.3 || x >= 0.8)
	{
		return 0;
	}
	else
	{
		float G = -3060 * (x - 0.3)*(x - 0.8);
		return static_cast<int>(G);
	}
}

int Renderer::ColorPicker::BlueSaturation(float x)
{
	if (x == 1)	return 0;

	if (x <= 0.6)
	{
		return 0;
	}
	else
	{
		float B = 255 * sqrt(x - 0.6);
		return static_cast<int>(B);
	}
}
