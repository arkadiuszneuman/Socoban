#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "BaseObject.h"

class MovableObject : public BaseObject
{
private:
	Point destination;
	float CalcMoveSpeed(float location, float destination);
protected:
	float moveSpeed;
	bool isMoving;
	///<summary>Okre�la ile klatek b�dzie w bie��cym ruchu</summary>
	int animFrames;
	MovableObject(Point &location);
public:
	void Move(Point destination);
	virtual void Update();
};

#endif