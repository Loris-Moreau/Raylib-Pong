#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"
#include "Text.h"

#include <RectangleI.h>
#include <Collisions.h>

#include <iostream>
#include <string>

using namespace std;

void Update();
void Draw();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

int result = 0;
char playerPoints;
char opponentPoints;

Text outcomeText = Text(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/3, "", 40, LIGHTGRAY);

Text playerScoreText = Text(100, 100, to_string(playerPoints), 20, LIGHTGRAY);
Text opponentScoreText = Text(SCREEN_WIDTH - 100, 100, to_string(opponentPoints), 20, LIGHTGRAY);

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
	int opponentPoints = 0;

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
	if (result == 0)
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

		RectangleI rightPaddleRect = rightPaddle.GetRect();

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

			opponentScoreText.SetText(to_string(opponentPoints));

			//you lose
			if (opponentPoints >= 5)
			{
				result = 2;
				outcomeText.SetText("You Lose");
			}
		}
		else if (ball.GetX() > SCREEN_WIDTH - ball.GetWidth())
		{
			++playerPoints;

			ball.SetX(SCREEN_WIDTH / 2);

			playerScoreText.SetText(to_string(playerPoints));

			if (playerPoints >= 5)
			{
				result = 1;
				outcomeText.SetText("You Win");
			}
		}
	}
	//end of the game
	else 
	{

	}
}

void Draw() 
{
	BeginDrawing();

	ClearBackground(BLACK);

	playerScoreText.Draw(); 

	ball.Draw();

	leftPaddle.Draw();
	rightPaddle.Draw(); 

	outcomeText.Draw();

	EndDrawing();
}
