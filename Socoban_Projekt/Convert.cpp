#include "Convert.h"
#include <sstream>

using namespace std;

int Convert::ToInt(string text)
{
	return atoi(text.c_str());
}

string Convert::ToString(int number)
{
	stringstream out;
	out << number;
	return out.str();
}