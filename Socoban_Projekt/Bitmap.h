#ifndef BITMAP_H
#define BITMAP_H

#include "allegro5\allegro.h"
#include <string>

class Bitmap
{
private:
	int width, height;
	ALLEGRO_BITMAP *bitmap;
public:
	Bitmap(std::string bitmapPath);
	~Bitmap();

	void Draw(int x, int y);

	int GetWidth();
	int GetHeight();
};

#endif