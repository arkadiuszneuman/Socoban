#ifndef HIGHSCOREDRAWER_H
#define HIGHSCOREDRAWER_H

#include "HighscoreDrawer.h"
#include "HighscoreCollection.h"
#include "Engine.h"
#include "Point.h"

class HighscoreDrawer
{
private:
	Engine *engine;
	int r,g,b, actualMap;
	float thick;
	Point location;

	void DrawPlayers(HighscoreCollection *highscore);
public:
	HighscoreDrawer(Point &location, int r, int g, int b, float thick);
	~HighscoreDrawer();
	void Draw(HighscoreCollection *highscore);
	void NextHighscore();
	void PrevHighscore();
};

#endif