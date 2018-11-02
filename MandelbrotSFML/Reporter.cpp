#include <thread>
#include "Reporter.hpp"
#include "Renderer.hpp"
#include "consoleUtilities.h"

void Reporter::ViewGenerationParameters(Renderer & renderer)
{
	cout << "Generation ranges: ";

	cout << "X(" << renderer.X1 << ", " << renderer.X2 << "), ";
	cout << "Y(" << renderer.Y1 << ", " << renderer.Y2 << ")" << endl;

	cout << "Calculation precison: " << Calculator::GetCalculationPrecision() << endl;
	cout << "Image size: " << renderer.imgWidth << ", " << renderer.imgHeight << endl;


}

void Reporter::ViewGenerationState(Renderer & renderer)
{
	numberOfPixels = renderer.imgWidth * renderer.imgHeight;

	std::cout << "Generation progress: ";

	int bufferXPos = wherex();
	int bufferYPos = wherey();

	CalculateGenerationState(renderer);
	cout << generation_progress;

	while (generation_progress < 100)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		
		CalculateGenerationState(renderer);

		gotoxy(bufferXPos, bufferYPos);
		std::cout << generation_progress << "%";

	}
	
	std::cout << std::endl << "Generation process finished" << std::endl;

}

void Reporter::GenerationTimeReport()
{
	cout << "Genearation time: " << timer.latestDuration() << endl;
}

void Reporter::CalculateGenerationState(Renderer & renderer)
{
	/*
	float width_progress = (float)renderer.width_it / (float)renderer.imgWidth;
	float height_progress = (float)renderer.height_it / (float)renderer.imgHeight;

	generation_progress = width_progress * height_progress * 100;
	*/
	generation_progress = (unsigned int)((float)Calculator::GetTestCallCount() 
						/ (float)numberOfPixels * 100);
	

}
