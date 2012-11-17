#ifndef CONVERT_H
#define CONVERT_H

#include <string>

using namespace std;

class Convert
{
public:
	static int ToInt(string text);
	static string ToString(int number);
};

#endif