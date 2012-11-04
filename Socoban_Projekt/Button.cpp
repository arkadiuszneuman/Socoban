#include "Button.h"
#include <sstream>

Button::Button(std::string name, Point &location)
	: BaseObject(location)
{
	for (int i = 0; i < 3; ++i)
	{
		std::stringstream out;
		out << i+1;
		std::string path = "Menu/" + name;
		path += out.str();
		path += ".bmp";
		
		bitmaps[i] = engine->GetBMP(path);
	}

	bitmap = bitmaps[0];
}

bool Button::IsMouseOver(Mouse mouse)
{
	Point size(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap));
	Point mouseLocation(mouse.x, mouse.y);

	if (mouseLocation >= this->location && mouseLocation <= size)
	{
		return true;
	}

	return false;
}

void Button::MouseMove(Mouse mouse)
{
	if (IsMouseOver(mouse))
	{
		bitmap = bitmaps[1];
	}
	else
	{
		bitmap = bitmaps[0];
	}
}

void Button::MouseDown(Mouse mouse)
{
}

void Button::MouseUp(Mouse mouse)
{
}

Button::~Button()
{

}