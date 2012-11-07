#include "Bitmap.h"

Bitmap::Bitmap(std::string bitmapPath)
{
	bitmap = NULL;

	std::string fileFolder = "";

	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(path, (fileFolder + bitmapPath).c_str());

	bitmap = al_load_bitmap(al_path_cstr(path, '/'));
	al_convert_mask_to_alpha(bitmap, al_map_rgb(255, 0, 255));

	if (bitmap == NULL)
	{
		throw "Blad wczytania bitmapy: " + bitmapPath;
	}
	
	al_destroy_path(path);

	this->width = al_get_bitmap_width(bitmap);
	this->height = al_get_bitmap_height(bitmap);
}

void Bitmap::Draw(int x, int y)
{
	al_draw_bitmap(bitmap, x, y, 0);
}

int Bitmap::GetWidth()
{
	return width;
}

int Bitmap::GetHeight()
{
	return height;
}

Bitmap::~Bitmap()
{
	if (bitmap != NULL)
	{
		al_destroy_bitmap(bitmap);
	}
}