#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

class Highscore
{
public:
	std::string PlayerName, Time;
	int Steps;

	Highscore();
};

#endif