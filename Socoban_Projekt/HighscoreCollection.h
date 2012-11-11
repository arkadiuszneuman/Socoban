#ifndef HIGHSCORECOLLECTION_H
#define HIGHSCORECOLLECTION_H

#include "Highscore.h"

class HighscoreCollection
{
private:
	///<summary>Zbór najlepszych wyników (10 plansz po 10 wyników)</summary>
	Highscore highscore[10][10];
public:
	HighscoreCollection();
};

#endif