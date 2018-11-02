#pragma once
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> compz;

class Calculator
{
	static unsigned int numberOfIterations;
	static int testCallCounter;

	static complex<double> complexFunction(complex<double> z, complex<double> P)
	{
		return z * z + P;
	}

public:
	static void SetCalculationPrecision(unsigned int iterations)
	{
		numberOfIterations = iterations;
	}

	// Function that tests if given complex number P satisfies the
	// Mandelbrot Set rule, according to given precision (number of iterations)
	static bool MandelbrotTest(complex<double> P)
	{
		complex<double> Z(0, 0);

		bool result = true;

		unsigned int i = 0;
		do
		{
			Z = complexFunction(Z, P); // Process the next sequence element

			result = (abs(Z) <= 2.0);

			i++;

		} while (i < numberOfIterations && result == true);

		//result = (abs(Z) <= 2.0);
		testCallCounter++;

		return result;
	}

	static unsigned int GetCalculationPrecision()
	{
		return numberOfIterations;
	}
	static int GetTestCallCount()
	{
		return testCallCounter;
	}

};

