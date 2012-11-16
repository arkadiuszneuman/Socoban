#ifndef ENGINE_H
#define ENGINE_H

#include "allegro5\allegro.h"
#include <string>
#include "IGame.h"
#include <map>
#include "IMouseEvents.h"
#include "IKeyboardEvents.h"
#include "Bitmap.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Engine
{
private:
	static const int FPS = 60;

	static Engine *eng;
	bool allegroInitialized;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_TIMER *timer;
	IGame *game;
	IMouseEvents *mouseEvents;
	IKeyboardEvents *keyboardEvents;
	ALLEGRO_FONT *font, *monospacedFont;
	///<summary>Zapamiêtuje wskaŸniki dla danej bitmapy - przy ponownym wczytaniu bitmapy nie bêdzie ona wczytywana ponownie, lecz zwracana z mapy</summary>
	std::map<std::string, Bitmap*> bitmapsPointiers;
	Engine();
public:
	void Initialize(std::string gameName);
	void DrawBitmap(Bitmap *bitmap, int x, int y);
	void DrawGameText(std::string text, int x, int y, int r, int g, int b, bool center, bool monospaced);
	void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, float thick);
	void DrawRectangle(int x1, int y1, int x2, int y2, int r, int g, int b, float thick);
	void StartGameLoop();
	void ShowError(std::string message);
	void AddEvents(IGame *game, IMouseEvents *mouseEvents, IKeyboardEvents *keyboardEvents);
	int GetDisplayWidth();
	int GetDisplayHeight();
	///<summary>Usuwa wszelkie bitmapy z pamiêci</summary>
	void DisposeBitmaps();
	Bitmap *GetBMP(std::string path);
	static Engine *GetInstance();
	bool endGameLoop;
	void Exit();
};

#endif