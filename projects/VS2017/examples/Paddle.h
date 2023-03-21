#pragma once

#ifndef INC_01_PONG_PADDLE_H 
#define INC_01_PONG_PADDLE_H

#include <RectangleI.h>

class Paddle 
{
public:
	Paddle();
	Paddle(int xP, int yP, int widthP, int heightP, int speedP);
	~Paddle();

	void Update();
	void Draw();

	void UpdateAI(int ballY);
	void MoveUp();
	void MoveDown();

	void ResetPaddle();

	RectangleI GetRect();

private:
	int x;
	int y;

	int width;
	int height;

	int speedY;
};

#endif