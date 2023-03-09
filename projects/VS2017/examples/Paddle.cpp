#include <raylib.h> 
#include "Paddle.h" 

Paddle::Paddle()
{
	width = 32; 
	height = 128; 
	speedY = 4;
	Paddle::x = 0;
	Paddle::y = 200;
}

Paddle::Paddle(int xP, int yP, int widthP, int heightP, int speedP) : x(xP), y(yP), width(widthP), height(heightP), speedY(speedP)
{

}

Paddle::~Paddle() 
{

}

void Paddle::Update() 
{
	if (IsKeyDown(KEY_UP))
	{
		y -= speedY;
		if (y < 0)
		{
			y = 0;
		}
	}
	int screenHeight = GetScreenHeight();
	if (IsKeyDown(KEY_DOWN))
	{
		y += speedY;
		if (y > screenHeight - height)
		{
			y = screenHeight - height;
		}
	}
}

void Paddle::Draw() 
{
	DrawRectangle(x, y, width, height, WHITE);
}
