#pragma once
#include <iostream>
#include <time.h>
using namespace std;

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

	void timeLapseReport()
	{
		
		
	}

};

