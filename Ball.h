#pragma once
#ifndef INC_01_PONG_BALL_H 
#define INC_01_PONG_BALL_H 

class Ball 
{
public:
	Ball();
	Ball(int xP, int yP, int sizeP, int speedP); 
	~Ball();

	void Update();
	void Draw();

private:
	int x;
	int y; 
	int size;
	int speedX;
	int speedY;
};

#endif 
