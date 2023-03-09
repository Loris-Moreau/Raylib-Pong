#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"

#include <iostream>
#include <string>

using namespace std;

void Update();
void Draw();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

Ball ball;
Paddle leftPaddle;

int main() 
{
	// Initialization 
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(60);

	ball = Ball(100, 100, 32, 7);
	leftPaddle = Paddle(0, 200, 32, 128, 4);

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
}

void Draw() 
{
	BeginDrawing();

	ClearBackground(BLACK);
	ball.Draw();
	leftPaddle.Draw();

	EndDrawing();
}
