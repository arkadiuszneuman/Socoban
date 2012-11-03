#include "allegro5\allegro.h"
#include <string>
#include "IGame.h"
#include <map>

#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
private:
	static Engine *eng;
	static bool allegroInitialized;
	static ALLEGRO_DISPLAY *display;
	static ALLEGRO_EVENT_QUEUE *eventQueue;
	static ALLEGRO_TIMER *timer;
	static const int FPS = 60;
	static IGame *game;
	void ShowError(std::string message);
	///<summary>Zapamiêtuje wskaŸniki dla danej bitmapy - przy ponownym wczytaniu bitmapy nie bêdzie ona wczytywana ponownie, lecz zwracana z mapy</summary>
	std::map<std::string, ALLEGRO_BITMAP*> bitmapsPointiers;
	Engine();
public:
	void Initialize(IGame *game, std::string gameName);
	void DrawBitmap(ALLEGRO_BITMAP *bitmap, int x, int y);
	void StartGameLoop();
	///<summary>Usuwa wszelkie bitmapy z pamiêci</summary>
	void DisposeBitmaps();
	ALLEGRO_BITMAP *GetBMP(std::string path);
	static Engine *GetInstance();
	bool endGameLoop;
	void Exit();
};

#endif