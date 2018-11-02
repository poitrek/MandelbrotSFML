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

