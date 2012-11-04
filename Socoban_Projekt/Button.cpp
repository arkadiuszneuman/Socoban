#include "Button.h"
#include <sstream>

Button::Button(std::string name, Point &location)
	: BaseObject(location)
{
	for (int i = 0; i < 3; ++i)
	{
		std::stringstream out;
		out << i+1;
		std::string path = name;
		path += out.str();
		path += ".bmp";
		
		bitmaps[i] = engine->GetBMP(path);
	}

	bitmap = bitmaps[0];
}