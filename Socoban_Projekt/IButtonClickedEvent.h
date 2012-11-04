#ifndef BUTTONCLICKEDEVENT_H
#define BUTTONCLICKEDEVENT_H

#include <string>

class IButtonClickedEvent
{
public:
	virtual void ButtonClicked(std::string buttonName) = 0;
};

#endif