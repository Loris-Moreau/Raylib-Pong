#include "raylib.h" 
#include "Ball.h"
#include "RectangleI.h"

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
		HorizontalBounce(0);
	}
	if (x > screenWidth - size)
	{
		HorizontalBounce(screenWidth - size);
	}
	if (y < 0)
	{
		VerticalBounce(0);
	}
	if (y > screenHeight - size)
	{
		VerticalBounce(screenHeight - size);
	}
}

void Ball::Draw() 
{
	DrawRectangle(x, y, size, size, WHITE);
}

RectangleI Ball::GetRectangle()
{
	return RectangleI { x, y, width, height };
}

void Ball::HorizontalBounce(int newX)
{
	speedX = -speedX;
	x = newX;
}

void Ball::VerticalBounce(int newY)
{
	speedY = -speedY;
	y = newY;
}