#include <iostream>
#include "Mathfuncsdll.h"
using namespace std;
int main()
{
	double a = 7.4;
	int b = 99;
	cout << "a + b = " <<
		Mathfuncs::Mymathfuncs::Add(a, b) << endl;
	cout << "a - b = " <<
		Mathfuncs::Mymathfuncs::Subtract(a, b) << endl;
	cout << "a * b = " <<
		Mathfuncs::Mymathfuncs::Multiply(a, b) << endl;
	cout << "a / b = " <<
		Mathfuncs::Mymathfuncs::Divide(a, b) << endl;
	try
	{
		cout << "a / 0 = " <<
			Mathfuncs::Mymathfuncs::Divide(a, 0) << endl;
	}
	catch (const invalid_argument& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}
	return 0;
}
