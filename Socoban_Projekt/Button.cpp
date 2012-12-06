#include "Button.h"
#include "BaseObject.h"
#include "Convert.h"

Button::Button(std::string name, Point &location, IButtonClickedEvent *buttonClickedEvent, bool threeState)
	: BaseObject(location)
{
	if (threeState)
	{
		for (int i = 0; i < 3; ++i)
		{
			std::string path = "Menu/" + name + Convert::ToString(i + 1) + ".bmp";
			bitmaps[i] = engine->GetBMP(path);
		}
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			std::string path = "Menu/" + name + ".bmp";
			bitmaps[i] = engine->GetBMP(path);
		}
	}

	bitmap = bitmaps[0];
	this->isMouseDown = false;
	this->name = name;
	this->buttonClickedEvent = buttonClickedEvent;
	this->threeState = threeState;
	Engine::GetInstance()->AddMouseEvent(this);
}

void Button::SetIsClickable(bool isClickable)
{
	this->isClickable = isClickable;
}

bool Button::IsMouseOver(Mouse mouse)
{
	if (isClickable)
	{
		Point size(bitmap->GetWidth(), bitmap->GetHeight());
		Point mouseLocation(mouse.x, mouse.y);

		if (mouseLocation >= this->location && mouseLocation <= this->location + size)
		{
			return true;
		}
	}

	return false;
}

void Button::MouseMove(Mouse mouse)
{
	if (isClickable)
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
}

void Button::MouseButtonDown(Mouse mouse)
{
	if (isClickable)
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
}

void Button::MouseButtonUp(Mouse mouse)
{
	if (isClickable)
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
}

Button::~Button()
{
	Engine::GetInstance()->RemoveMouseEvent(this);
}