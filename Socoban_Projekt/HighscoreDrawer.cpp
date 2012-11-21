#include "HighscoreDrawer.h"
#include "Convert.h"

HighscoreDrawer::HighscoreDrawer(Point &location, int r, int g, int b, float thick)
{
	this->location = location;

	this->r = r;
	this->b = b;
	this->g = g;
	this->actualMap = 0;

	this->thick = thick;
	this->engine = Engine::GetInstance();
}

void HighscoreDrawer::Draw(HighscoreCollection *highscore)
{
	engine->DrawRectangle(location.GetX(), location.GetY(), 
		location.GetX() + 365, location.GetY() + 300, r, g, b, thick);

	engine->DrawLine(location.GetX() + 35, location.GetY(), 
		location.GetX() + 35, location.GetY() + 300, r, g, b, thick);

	engine->DrawLine(location.GetX() + 195, location.GetY(), 
		location.GetX() + 195, location.GetY() + 300, r, g, b, thick);

	engine->DrawLine(location.GetX() + 295, location.GetY(), 
		location.GetX() + 295, location.GetY() + 300, r, g, b, thick);

	engine->DrawLine(location.GetX(), location.GetY() + 30, 
		location.GetX() + 365, location.GetY() + 30, r, g, b, thick);

	engine->DrawGameText("Lp.", location.GetX() + 5, location.GetY() + 3, r, g, b, false, false);
	engine->DrawGameText("Imie", location.GetX() + 40, location.GetY() + 3, r, g, b, false, false);
	engine->DrawGameText("Czas", location.GetX() + 200, location.GetY() + 3, r, g, b, false, false);
	engine->DrawGameText("Kroki", location.GetX() + 300, location.GetY() + 3, r, g, b, false, false);

	DrawPlayers(highscore);

	engine->DrawGameText("Plansza: " + Convert::ToString(actualMap + 1), (location.GetX() + 365) / 2, location.GetY() - 40, r, g, b, true, false);
}

void HighscoreDrawer::DrawPlayers(HighscoreCollection *highscore)
{
	for (int i = 0; i < 10; ++i)
	{
		Highscore h = highscore->GetHighscore(actualMap, i);

		engine->DrawGameText(Convert::ToString(i + 1) + ".", location.GetX() + 5, (location.GetY() + 30) + i * 27, r, g, b, false, false);
		engine->DrawGameText(h.PlayerName, location.GetX() + 40, (location.GetY() + 30) + i * 27, r, g, b, false, false);
		engine->DrawGameText(h.Time, location.GetX() + 200, (location.GetY() + 30) + i * 27, r, g, b, false, false);
		engine->DrawGameText(Convert::ToString(h.Steps), location.GetX() + 300, (location.GetY() + 30) + i * 27, r, g, b, false, false);
	}
}

void HighscoreDrawer::NextHighscore()
{
	if (actualMap < 9)
		++actualMap;
}

void HighscoreDrawer::PrevHighscore()
{
	if (actualMap > 0)
		--actualMap;
}

HighscoreDrawer::~HighscoreDrawer()
{
	
}