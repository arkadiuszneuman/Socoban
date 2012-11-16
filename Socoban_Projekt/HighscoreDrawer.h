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
	int r,g,b;
	float thick;
	Point *location;
public:
	HighscoreDrawer(Point *location, int r, int g, int b, float thick);
	~HighscoreDrawer();
	void Draw(HighscoreCollection *highscore);
};

#endif