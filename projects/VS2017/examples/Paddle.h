#pragma once

#ifndef INC_01_PONG_PADDLE_H 
#define INC_01_PONG_PADDLE_H 

class Paddle 
{
public:
	Paddle();
	Paddle(int xP, int yP, int widthP, int heightP, int speedP);
	~Paddle();

	void Update();
	void Draw();

private:
	int x;
	int y;

	int width;
	int height;

	int speedY;
};

#endif