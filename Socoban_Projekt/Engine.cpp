#include "Engine.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "Mouse.h"

Engine *Engine::eng = NULL;


Engine::Engine()
{
	endGameLoop = false;
	game = NULL;
	allegroInitialized = false;
	display = NULL;
	eventQueue = NULL;
	timer = NULL;
	font = NULL;
}

void Engine::Initialize(std::string gameName)
{
	if (!allegroInitialized)
	{
		if (!al_init())
		{
			ShowError("Blad podczas inicjalizacji allegro.");
			return;
		}

		if (!al_install_keyboard())
		{
			ShowError("Blad podczas inicjalizacji klawiatury.");
			return;
		}

		if(!al_install_mouse()) 
		{
			ShowError("Blad podczas inicjalizacji myszy.");
			return;
		}
		
		display = al_create_display(800, 600);
		if (!display) 
		{
			ShowError("Blad podczas inicjalizacji.");
			return;
		}

		al_init_primitives_addon();
		al_init_font_addon();
		al_init_ttf_addon();

		font = al_load_ttf_font("tahoma.ttf", 20, 0);
		if (!font) 
		{
			ShowError("Blad podczas inicjalizacji czcionki.");
			return;
		}

		monospacedFont = al_load_ttf_font("courier.ttf", 15, 0);
		if (!monospacedFont) 
		{
			ShowError("Blad podczas inicjalizacji czcionki.");
			return;
		}

		al_set_window_title(display, gameName.c_str());

		timer = al_create_timer(1.0 / FPS);
		if (!timer) 
		{
			ShowError("Blad podczas tworzenia timera.");
			return;
		}

		eventQueue = al_create_event_queue();
		if (!eventQueue) 
		{
			ShowError("Blad podczas inicjalizacji kolejki.");
			return;
		}
 
		al_register_event_source(eventQueue, al_get_display_event_source(display));
		al_register_event_source(eventQueue, al_get_timer_event_source(timer));
		al_register_event_source(eventQueue, al_get_keyboard_event_source());
		al_register_event_source(eventQueue, al_get_mouse_event_source());

		al_init_image_addon();

		allegroInitialized = true;
	}
}

void Engine::AddEvents(IGame *game)
{
	this->game = game;
	this->mouseEvents = mouseEvents;
}

void Engine::AddKeyboardEvent(IKeyboardEvents *keyboardEvent)
{
	keyboardEvents.push_back(keyboardEvent);
}

void Engine::RemoveKeyboardEvent(IKeyboardEvents *keyboardEvent)
{
	for (int i = 0; i < keyboardEvents.size(); ++i)
	{
		if (keyboardEvents[i] == keyboardEvent)
		{
			keyboardEvents.erase(keyboardEvents.begin() + i);
			break;
		}
	}

	keyboardEvents.clear();
}

void Engine::AddMouseEvent(IMouseEvents *mouseEvent)
{
	mouseEvents.push_back(mouseEvent);
}

void Engine::RemoveMouseEvent(IMouseEvents *mouseEvent)
{
	for (int i = 0; i < mouseEvents.size(); ++i)
	{
		if (mouseEvents[i] == mouseEvent)
		{
			mouseEvents.erase(mouseEvents.begin() + i);
			break;
		}
	}
}

void Engine::ShowError(std::string message)
{
	al_show_native_message_box(al_get_current_display(), 
									 "Socoban", 
									 "Error", 
									 message.c_str(),
									 NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

void Engine::DrawBitmap(Bitmap *bitmap, int x, int y)
{
	bitmap->Draw(x, y);
}

void Engine::DrawGameText(std::string text, int x, int y, int r, int g, int b, bool center, bool monospaced)
{
	int flag = center ? ALLEGRO_ALIGN_CENTRE : ALLEGRO_ALIGN_LEFT;
	ALLEGRO_FONT *f = monospaced ? monospacedFont : font;

	al_draw_text(f, al_map_rgb(r, g, b), x, y, flag, text.c_str());
}

void Engine::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, float thick)
{
	al_draw_line(x1, y1, x2, y2, al_map_rgb(r, g, b), thick);
	
}

void Engine::DrawRectangle(int x1, int y1, int x2, int y2, int r, int g, int b, float thick)
{
	al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(r, g, b), thick);
}

int Engine::GetDisplayWidth()
{
	return al_get_display_width(display);
}

int Engine::GetDisplayHeight()
{
	return al_get_display_height(display);
}

Bitmap *Engine::GetBMP(std::string filePath)
{
	if (bitmapsPointiers.count(filePath))
	{
		return bitmapsPointiers[filePath];
	}
	else
	{
		Bitmap *bmp = new Bitmap("graphics/" + filePath);

		bitmapsPointiers[filePath] = bmp;

		return bmp;
	}
}

void Engine::StartGameLoop()
{
	Mouse mouse;

	bool redraw = false;
	al_start_timer(timer);
 
	while(!endGameLoop)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);
 
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			game->Update();

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			Key key = (Key)ev.keyboard.keycode;
			for (int i = 0; i < keyboardEvents.size(); ++i)
			{
				keyboardEvents[i]->KeyDownEvent(key);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) 
		{
			Key key = (Key)ev.keyboard.keycode;
			for (int i = 0; i < keyboardEvents.size(); ++i)
			{
				keyboardEvents[i]->KeyUpEvent(key);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
		{
			char c = (char)ev.keyboard.unichar;
			for (int i = 0; i < keyboardEvents.size(); ++i)
			{
				keyboardEvents[i]->CharEntered(c);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			  ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			mouse.x = ev.mouse.x;
			mouse.y = ev.mouse.y;
			mouse.button = ev.mouse.button;

			for (int i = 0; i < mouseEvents.size(); ++i)
			{
				mouseEvents[i]->MouseMove(mouse);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			mouse.x = ev.mouse.x;
			mouse.y = ev.mouse.y;
			mouse.button = ev.mouse.button;

			for (int i = 0; i < mouseEvents.size(); ++i)
			{
				mouseEvents[i]->MouseButtonUp(mouse);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			mouse.x = ev.mouse.x;
			mouse.y = ev.mouse.y;
			mouse.button = ev.mouse.button;

			for (int i = 0; i < mouseEvents.size(); ++i)
			{
				mouseEvents[i]->MouseButtonDown(mouse);
			}
		}
 
		if(redraw && al_is_event_queue_empty(eventQueue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));

			game->Draw();

			al_flip_display();
		}
	}
}

Engine *Engine::GetInstance()
{
	if (eng == NULL)
	{
		eng = new Engine();
	}

	return eng;
}

void Engine::DisposeBitmaps()
{
	for (std::map<std::string, Bitmap*>::const_iterator iterator = bitmapsPointiers.begin(); iterator != bitmapsPointiers.end(); ++iterator)
	{
		delete iterator->second;
	}

	bitmapsPointiers.clear();
}

void Engine::Exit()
{
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_font(font);
	al_destroy_font(monospacedFont);

	DisposeBitmaps();

	delete eng;
}