#include "HighscoreDrawer.h"

HighscoreDrawer::HighscoreDrawer(Point *location, int r, int g, int b, float thick)
{
	this->location = location;

	this->r = r;
	this->b = b;
	this->g = g;

	this->thick = thick;
	this->engine = Engine::GetInstance();
}

void HighscoreDrawer::Draw(HighscoreCollection *highscore)
{
	engine->DrawRectangle(location->GetX(), location->GetY(), 
		location->GetX() + 365, location->GetY() + 300, r, g, b, thick);

	engine->DrawLine(location->GetX() + 35, location->GetY(), 
		location->GetX() + 35, location->GetY() + 300, r, g, b, thick);

	engine->DrawLine(location->GetX() + 195, location->GetY(), 
		location->GetX() + 195, location->GetY() + 300, r, g, b, thick);

	engine->DrawLine(location->GetX() + 295, location->GetY(), 
		location->GetX() + 295, location->GetY() + 300, r, g, b, thick);

	engine->DrawLine(location->GetX(), location->GetY() + 30, 
		location->GetX() + 365, location->GetY() + 30, r, g, b, thick);


	//engine->DrawLine(

	/*hline(bufor, 0, 205, 365, Kbialy);
	hline(bufor, 0, 232, 365, Kbialy);
	hline(bufor, 0, 259, 365, Kbialy);
	hline(bufor, 0, 286, 365, Kbialy);
	hline(bufor, 0, 313, 365, Kbialy);
	hline(bufor, 0, 340, 365, Kbialy);
	hline(bufor, 0, 367, 365, Kbialy);
	hline(bufor, 0, 394, 365, Kbialy);
	hline(bufor, 0, 421, 365, Kbialy);
	hline(bufor, 0, 448, 365, Kbialy);*/
}

HighscoreDrawer::~HighscoreDrawer()
{
	delete location;
}