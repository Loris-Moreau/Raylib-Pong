#include "raylib.h" 
#include "Ball.h" 

Ball::Ball() 
{
	x = 0;
	y = 0;

	size = 32;

	speedX = 4;
	speedY = 4;
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

	/*if (x < 0)
	{
		HorizontalBounce(0);
	}
	if (x > screenWidth - size)
	{
		HorizontalBounce(screenWidth - size);
	}*/

	if (y < 0)
	{
		PlaySound(wallSound);

		VerticalBounce(0);
	}
	if (y > screenHeight - size)
	{
		PlaySound(wallSound);

		VerticalBounce(screenHeight - size);
	}
}

int Ball::GetX() const
{
	return x;
}

void Ball :: SetX(int xP)
{
	x = xP;
}

int Ball::GetWidth() const
{
	return size;
}

void Ball::Draw() 
{
	DrawRectangle(x, y, size, size, WHITE);
}

RectangleI Ball::GetRect()
{
	return RectangleI { x, y, size, size };
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