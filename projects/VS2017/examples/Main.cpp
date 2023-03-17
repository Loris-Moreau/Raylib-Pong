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

int playerPoints = 0;
int opponentPoints = 0;

Text outcomeText = Text(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/3, "", 40, LIGHTGRAY);

Text playerScoreText = Text(100, 100, to_string(playerPoints), 20, LIGHTGRAY);
Text opponentScoreText = Text(SCREEN_WIDTH - 100, 100, to_string(opponentPoints), 20, LIGHTGRAY);

Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;

Sound pingSound;
Sound opponentPingSound;
Sound outSound;
Sound wallSound;
Sound victorySound;
Sound defeatSound;
Sound restartSound;

int main() 
{
	// Initialization 
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong of Doom");
	SetTargetFPS(60);

	//init audio
	InitAudioDevice();
	pingSound = LoadSound("assets/ping.wav");
	opponentPingSound = LoadSound("assets/oponentPing.wav");
	outSound = LoadSound("assets/out.wav");
	wallSound = LoadSound("assets/wall.wav");
	victorySound = LoadSound("assets/victory.wav");
	defeatSound = LoadSound("assets/defeat.wav");
	restartSound = LoadSound("assets/restart.wav");

	ball = Ball(100, 100, 32, 10);

	leftPaddle = Paddle(0, 200, 32, 128, 7);
	rightPaddle = Paddle(SCREEN_WIDTH - 32, 200, 32, 128, 7);

	// Main game loop 
	while (!WindowShouldClose()) // Detect window close button or ESC key 
	{
		Update(); 
		Draw();
	}

	//unload sounds when game close
	UnloadSound(pingSound);
	UnloadSound(opponentPingSound);
	UnloadSound(outSound);
	UnloadSound(wallSound);
	UnloadSound(victorySound);
	UnloadSound(defeatSound);
	UnloadSound(restartSound);
	CloseAudioDevice();

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

			PlaySound(pingSound);
		}

		RectangleI rightPaddleRect = rightPaddle.GetRect();

		colliding = Collisions::AABBCollision(ballRect, rightPaddleRect);
		if (colliding)
		{
			ball.HorizontalBounce(rightPaddleRect.x - ballRect.width);

			PlaySound(opponentPingSound);
		}

		rightPaddle.UpdateAI(ballRect.y);
		//leftPaddle.UpdateAI(ballRect.y);

		//points system
		if (ball.GetX() < 0)
		{
			++opponentPoints;

			ball.SetX(SCREEN_WIDTH / 2);

			opponentScoreText.SetText(to_string(opponentPoints));

			PlaySound(outSound);

			//you lose
			if (opponentPoints >= 5)
			{
				result = 2;
				outcomeText.SetText("You Lose");
				PlaySound(defeatSound);
			}
		}
		else if (ball.GetX() > SCREEN_WIDTH - ball.GetWidth())
		{
			++playerPoints;

			ball.SetX(SCREEN_WIDTH / 2);

			playerScoreText.SetText(to_string(playerPoints));

			PlaySound(outSound);

			if (playerPoints >= 5)
			{
				result = 1;
				outcomeText.SetText("You Win");
				PlaySound(victorySound);
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
	opponentScoreText.Draw();

	ball.Draw();

	leftPaddle.Draw();
	rightPaddle.Draw(); 

	outcomeText.Draw();

	EndDrawing();
}
