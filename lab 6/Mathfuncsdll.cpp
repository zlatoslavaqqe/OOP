#include "pch.h"
#include "Mathfuncsdll.h"
#include <stdexcept>
using namespace std;
namespace Mathfuncs
{
	double Mymathfuncs::Add(double a, double b)
	{
		return a + b;
	}
	double Mymathfuncs::Subtract(double a, double b)
	{
		return a - b;
	}
	double Mymathfuncs::Multiply(double a, double b)
	{
		return a * b;
	}
	double Mymathfuncs::Divide(double a, double b)
	{
		if (b == 0)
		{
			throw invalid_argument("b cannot be zero!");
		}
		return a / b;
	}
}
