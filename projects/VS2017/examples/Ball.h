#pragma once

#ifndef INC_01_PONG_BALL_H 
#define INC_01_PONG_BALL_H 

#include <RectangleI.h>

class Ball 
{
public:
	Ball();
	Ball(int xP, int yP, int sizeP, int speedP); 
	~Ball();

	void Update();
	void Draw();

	void HorizontalBounce(int newX);
	void VerticalBounce(int newY);

	RectangleI GetRect();

	int GetX() const;
	void SetX(int xP);

	int GetWidth() const;

private:
	int x;
	int y; 

	int size;

	int speedX;
	int speedY;

	Sound wallSound;
};

#endif 
