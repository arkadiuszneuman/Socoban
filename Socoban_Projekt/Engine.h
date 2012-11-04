#ifndef ENGINE_H
#define ENGINE_H

#include "allegro5\allegro.h"
#include <string>
#include "IGame.h"
#include <map>
#include "IMouseEvents.h"

class Engine
{
private:
	static Engine *eng;
	static bool allegroInitialized;
	static ALLEGRO_DISPLAY *display;
	static ALLEGRO_EVENT_QUEUE *eventQueue;
	static ALLEGRO_TIMER *timer;
	static const int FPS = 60;
	IGame *game;
	IMouseEvents *mouseEvents;
	///<summary>Zapami�tuje wska�niki dla danej bitmapy - przy ponownym wczytaniu bitmapy nie b�dzie ona wczytywana ponownie, lecz zwracana z mapy</summary>
	std::map<std::string, ALLEGRO_BITMAP*> bitmapsPointiers;
	Engine();
public:
	void Initialize(std::string gameName);
	void DrawBitmap(ALLEGRO_BITMAP *bitmap, int x, int y);
	void StartGameLoop();
	void ShowError(std::string message);
	void AddEvents(IGame *game, IMouseEvents *mouseEvents);
	///<summary>Usuwa wszelkie bitmapy z pami�ci</summary>
	void DisposeBitmaps();
	ALLEGRO_BITMAP *GetBMP(std::string path);
	static Engine *GetInstance();
	bool endGameLoop;
	void Exit();
};

#endif