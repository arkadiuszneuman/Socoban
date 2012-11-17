#ifndef HIGHSCORECOLLECTION_H
#define HIGHSCORECOLLECTION_H

#include "Highscore.h"
#include <vector>
#include <time.h>

class HighscoreCollection
{
private:
	///<summary>Zbór najlepszych wyników (10 plansz po 10 wyników)</summary>
	Highscore highscores[10][10];
	//std::vector<std::vector<Highscore> > highscores;
	void SaveHighscore();
	void LoadHighscore();
	bool IsHighscoreExists();

	std::vector<std::string> SplitString(const std::string &s, char delim);
	bool IsFaster(const std::string &time1, const std::string &time2);
public:
	HighscoreCollection();
	bool IsQualified(int mapNo, int steps, std::string time);
	void AddHighscore(int mapNo, std::string playerName, std::string time, int steps);
	Highscore GetHighscore(int mapNo, int position);
};

#endif