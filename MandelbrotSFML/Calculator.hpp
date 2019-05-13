#pragma once
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> compz;

class Calculator
{
	static unsigned int maximumIterations;
	static int testCallCounter;

	static complex<double> complexFunction(complex<double> z, complex<double> P)
	{
		return z * z + P;
	}

public:
	static void SetCalculationPrecision(unsigned int iterations)
	{
		maximumIterations = iterations;
	}

	// Returns the number of iterations needed for the processed
	// complex number to exceed 2.0 at its absolute value (if the
	// number reaches maximum given number of iterations then it's
	// considered to be inside of the Mandelbrot set
	static int MandelbrotTest(complex<double> P)
	{
		complex<double> Z(0, 0);

		int iterationsDone = 0;

		bool condition;

		do
		{
			Z = complexFunction(Z, P); // Process the next sequence element

			///result = (abs(Z) <= 2.0);

			// This operation is much faster
			// (calculating vector's norm instead of absolute value)
			condition = (norm(Z) <= 4.0);

			iterationsDone++;

		} while (iterationsDone < maximumIterations && condition == true);

		//result = (abs(Z) <= 2.0);
		testCallCounter++;

		return iterationsDone;
	}

	static unsigned int GetCalculationPrecision()
	{
		return maximumIterations;
	}
	static int GetTestCallCount()
	{
		return testCallCounter;
	}

};

