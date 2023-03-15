#include "raylib.h" 
#include "Ball.h" 

Ball::Ball() 
{
	x = 0;
	y = 0;
	size = 32;
	speedX = 2;
	speedY = 2;
}

Ball::Ball(int xP, int yP, int sizeP, int speedP) : x(xP), y(yP), size(sizeP), speedX(speedP), speedY(speedP)
{

}

Ball::~Ball() 
{

}

void Ball::Update() 
{
	x += speedX;
	y += speedY;

	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	if (x < 0)
	{
		speedX = -speedX;
		x = 0;
	}
	if (x > screenWidth - size)
	{
		speedX = -speedX;
		x = screenWidth - size;
	}
	if (y < 0)
	{
		speedY = -speedY;
		y = 0;
	}
	if (y > screenHeight - size)
	{
		speedY = -speedY;
		y = screenHeight - size;
	}
}

void Ball::Draw() 
{
	DrawRectangle(x, y, size, size, WHITE);
}
