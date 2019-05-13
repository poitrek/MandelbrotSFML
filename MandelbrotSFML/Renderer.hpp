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

	struct ColorPicker
	{
		int RedSaturation(float);
		int GreenSaturation(float);
		int BlueSaturation(float);		
	}colorPicker;

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

	void GenerateImage();
	

	void loadSprite()
	{
		txtr.loadFromImage(img);

		sprite.setTexture(txtr);
	}
};

