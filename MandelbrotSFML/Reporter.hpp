#pragma once
#include <iostream>
#include <time.h>
#include "Calculator.hpp"
//#include "consoleUtilities.h"


using namespace std;

class Renderer;

class Reporter
{
public:
	class Timer
	{
		clock_t _start, _stop;
	public:
		void start()
		{
			_start = clock();
		}
		void stop()
		{
			_stop = clock();
		}
		double latestDuration()
		{
			return (double)(_stop - _start) / CLOCKS_PER_SEC;
		}

	}timer;

	void ViewGenerationParameters(Renderer &renderer);

	void ViewGenerationState(Renderer &renderer);

	void GenerationTimeReport();

private:
	void CalculateGenerationState(Renderer &renderer);

	unsigned int generation_progress{ 0 };

	unsigned int numberOfPixels;

};

