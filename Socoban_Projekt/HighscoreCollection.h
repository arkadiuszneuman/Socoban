#ifndef HIGHSCORECOLLECTION_H
#define HIGHSCORECOLLECTION_H

#include "Highscore.h"

class HighscoreCollection
{
private:
	///<summary>Zb�r najlepszych wynik�w (10 plansz po 10 wynik�w)</summary>
	Highscore highscore[10][10];
public:
	HighscoreCollection();
};

#endif