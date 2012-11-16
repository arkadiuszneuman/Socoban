#ifndef IKEYBOARDEVENTS_H
#define IKEYBOARDEVENTS_H

class IKeyboardEvents
{
public:
	virtual void KeyDownEvent(Key key) = 0;
	virtual void KeyUpEvent(Key key) = 0;

	virtual void CharEntered(char c) = 0;
};

#endif