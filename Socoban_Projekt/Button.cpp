#include "Button.h"
#include "BaseObject.h"
#include "Convert.h"

Button::Button(std::string name, Point &location, IButtonClickedEvent *buttonClickedEvent)
	: BaseObject(location)
{
	for (int i = 0; i < 3; ++i)
	{
		std::string path = "Menu/" + name + Convert::ToString(i + 1) + ".bmp";
		bitmaps[i] = engine->GetBMP(path);
	}

	bitmap = bitmaps[0];
	this->isMouseDown = false;
	this->name = name;
	this->buttonClickedEvent = buttonClickedEvent;
}

bool Button::IsMouseOver(Mouse mouse)
{
	Point size(bitmap->GetWidth(), bitmap->GetHeight());
	Point mouseLocation(mouse.x, mouse.y);

	if (mouseLocation >= this->location && mouseLocation <= this->location + size)
	{
		return true;
	}

	return false;
}

void Button::MouseMove(Mouse mouse)
{
	if (!isMouseDown)
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
}

void Button::MouseDown(Mouse mouse)
{
	if (IsMouseOver(mouse))
	{
		bitmap = bitmaps[2];
		isMouseDown = true;
	}
	else
	{
		bitmap = bitmaps[0];
	}
}

void Button::MouseUp(Mouse mouse)
{
	if (isMouseDown)
	{
		isMouseDown = false;

		if (IsMouseOver(mouse))
		{
			bitmap = bitmaps[1];
			buttonClickedEvent->ButtonClicked(name);
		}
		else
		{
			bitmap = bitmaps[0];
		}
	}
}

Button::~Button()
{

}