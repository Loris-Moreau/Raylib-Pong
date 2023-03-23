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
void Restart();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

int result = 0;

int playerPoints = 0;
int opponentPoints = 0;

#pragma region Text
Text outcomeText = Text(SCREEN_WIDTH/2 - 64, SCREEN_HEIGHT/2, "", 40, LIGHTGRAY);

Text playerScoreText = Text(100, 100, to_string(playerPoints), 20, LIGHTGRAY);
Text opponentScoreText = Text(SCREEN_WIDTH - 100, 100, to_string(opponentPoints), 20, LIGHTGRAY);
#pragma endregion

Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;

#pragma region Sounds
Sound pingSound;
Sound opponentPingSound;
Sound outSound;
Sound wallSound;
Sound victorySound;
Sound defeatSound;
Sound restartSound;
#pragma endregion

int main() 
{
	//Initialization 
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong of Doom");
	SetTargetFPS(60);

	//init sounds
	#pragma region init audio
	InitAudioDevice();

	pingSound = LoadSound("../assets/ping.wav");

	opponentPingSound = LoadSound("../assets/oponentPing.wav");

	outSound = LoadSound("../assets/out.wav");

	wallSound = LoadSound("../assets/wall.wav");

	victorySound = LoadSound("../assets/victory.wav");

	defeatSound = LoadSound("../assets/defeat.wav");

	restartSound = LoadSound("../assets/restart.wav");
	#pragma endregion

	ball = Ball(100, 100, 32, 10, wallSound);

	//Paddles
	leftPaddle = Paddle(0, 200, 32, 128, 7);
	rightPaddle = Paddle(SCREEN_WIDTH - 32, 200, 32, 128, 7);

	// Main game loop 
	while (!WindowShouldClose()) //Detect window close button or ESC key 
	{
		if (IsKeyDown(KEY_R))
		{
			Restart();
		}

		Update(); 
		Draw();
	}
	
	//unload sounds
	#pragma region unload sounds when game close
	UnloadSound(pingSound);
	UnloadSound(opponentPingSound);
	UnloadSound(outSound);
	UnloadSound(wallSound);
	UnloadSound(victorySound);
	UnloadSound(defeatSound);
	UnloadSound(restartSound);

	//CloseAudioDevice();
	#pragma endregion

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

		//collisions
		#pragma region Collisions
		RectangleI ballRect = ball.GetRect();
		RectangleI leftPaddleRect = leftPaddle.GetRect();

		bool colliding = Collisions::AABBCollision(ballRect, leftPaddleRect);
		if (colliding)
		{
			ball.HorizontalBounce(leftPaddleRect.x + leftPaddleRect.width);

			PlaySoundMulti(pingSound);
		}

		RectangleI rightPaddleRect = rightPaddle.GetRect();

		colliding = Collisions::AABBCollision(ballRect, rightPaddleRect);
		if (colliding)
		{
			ball.HorizontalBounce(rightPaddleRect.x - ballRect.width);

			PlaySoundMulti(opponentPingSound);
		}
		#pragma endregion

		rightPaddle.UpdateAI(ballRect.y);
		leftPaddle.UpdateAI(ballRect.y);

		//points
		#pragma region points system
		if (ball.GetX() < 0)
		{
			//you lose a point
			++opponentPoints;

			//over here : the ball needs to go towards the one that won a point
//------------------------------------------------------------------------------------------------------------------------
			ball.SetX(SCREEN_WIDTH / 2);
			ball.HorizontalBounce(SCREEN_WIDTH/2);
//------------------------------------------------------------------------------------------------------------------------

			opponentScoreText.SetText(to_string(opponentPoints));

			PlaySoundMulti(outSound);

			//you lose the game
			if (opponentPoints >= 5)
			{
				result = 2;
				outcomeText.SetText("You Lose");

				PlaySoundMulti(defeatSound);
			}
		}
		else if (ball.GetX() > SCREEN_WIDTH - ball.GetWidth())
		{
			//you gain a point
			++playerPoints;

			//here too
//------------------------------------------------------------------------------------------------------------------------
			ball.SetX(SCREEN_WIDTH / 2);
			ball.HorizontalBounce(SCREEN_WIDTH/2);
//------------------------------------------------------------------------------------------------------------------------

			playerScoreText.SetText(to_string(playerPoints));

			PlaySoundMulti(outSound);

			//you win the game
			if (playerPoints >= 5)
			{
				result = 1;
				outcomeText.SetText("You Win");

				PlaySoundMulti(victorySound);
			}
		}
		#pragma endregion
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

void Restart() //done
{
	PlaySoundMulti(restartSound);

	//resets points
	playerPoints = 0;
	opponentPoints = 0;

	result = 0;

	//resets text
	outcomeText.SetText("");
	playerScoreText.SetText("0");
	opponentScoreText.SetText("0");

	//Reset Ball
	ball.SetX(SCREEN_WIDTH / 2);

	//resets paddels
	leftPaddle.ResetPaddle(0, 200);
	rightPaddle.ResetPaddle(SCREEN_WIDTH - 32, 200);
}