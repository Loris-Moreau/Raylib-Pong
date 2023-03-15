#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"

#include <iostream>
#include <string>
#include <Recctangle.h>
#include <Collisions.h>

using namespace std;

void Update();
void Draw();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;

int main() 
{
	// Initialization 
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(60);

	ball = Ball(100, 100, 32, 7);

	leftPaddle = Paddle(0, 200, 32, 128, 4);
	rightPaddle = Paddle(SCREEN_WIDTH - 32, 200, 32, 128, 4);

	int playerPoints = 0;
	int enemyPoints = 0;

	// Main game loop 
	while (!WindowShouldClose()) // Detect window close button or ESC key 
	{
		Update(); 
		Draw();
	}
	CloseWindow(); 
	return 0;

	// Close window and OpenGL context 
}

void Update() 
{
	ball.Update();
	leftPaddle.Update();

	RectangleI ballRect = ball.GetRect();
	RectangleI leftPaddleRect = leftPaddle.GetRect();

	bool colliding = Collisions::AABBCollision(ballRect, leftPaddleRect);
	if (colliding)
	{
		ball.HorizontalBounce(leftPaddleRect.x + leftPaddleRect.width);
	}

	RectangleI rightPaddleRect = rightPaddle.GetRectangle();

	colliding = Collisions::AABBCollision(ballRect, rightPaddleRect);
	if (colliding)
	{
		ball.HorizontalBounce(rightPaddleRect.x - ballRect.width);
	}

	rightPaddle.UpdateAI(ballRect.y);

	//points system
	if (ball.GetX() < 0) 
	{
		++opponentPoints;
		ball.SetX(SCREEN_WIDTH / 2);
	} 
	else if (ball.GetX() > SCREEN_WIDTH - ball.GetWidth())
	{
		++playerPoints;
		ballSetx(SCREEN_WIDTH / 2);
	}
}

void Draw() 
{
	BeginDrawing();

	ClearBackground(BLACK);

	ball.Draw();

	leftPaddle.Draw();
	rightPaddle.Draw(); 

	EndDrawing();
}
