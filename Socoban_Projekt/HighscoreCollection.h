#ifndef HIGHSCORECOLLECTION_H
#define HIGHSCORECOLLECTION_H

#include "Highscore.h"
#include <vector>

class HighscoreCollection
{
private:
	///<summary>Zbór najlepszych wyników (10 plansz po 10 wyników)</summary>
	//Highscore highscores[10][10];
	//std::vector<std::vector<Highscore> > highscores;
public:
	HighscoreCollection();
	~HighscoreCollection();
};

#endif