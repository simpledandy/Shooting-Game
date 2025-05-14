//---------------------------------------------------------------------------

#include <vcl.h>
#include <mmsystem.h>
#include <vector>
#include <windows.h>
#pragma hdrstop

#include "ShootingGameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGameForm *GameForm;

// Game constants
const int WIN_CONDITION = 10;
const int EASY_SPEED = 10;
const int HARD_SPEED = 20;
const int INVADER_DROP = 15;

const int FIRST_ROW_TOP = 80;
const int SECOND_ROW_TOP = FIRST_ROW_TOP + 50;
const int THIRD_ROW_TOP = SECOND_ROW_TOP + 50;



// Game variables
int gameSpeed = EASY_SPEED;
int playerX;
int playerY;
int invadersRemaining = WIN_CONDITION;

// Helper functions
bool IsHit(TImage *bullet, TImage *enemy)
{
	return (bullet->Left >= (enemy->Left) - (bullet->Width) &&
			bullet->Left <= enemy->Left + enemy->Width &&
			bullet->Top >= enemy->Top - bullet->Height &&
			bullet->Top <= enemy->Top + enemy->Height &&
			bullet->Visible);
}

bool IsCollision(TImage *enemy, TImage *playerShip)
{
	return (enemy->Top > (playerShip->Top - enemy->Height) && enemy->Visible);
}

//---------------------------------------------------------------------------
__fastcall TGameForm::TGameForm(TComponent* Owner)
	: TForm(Owner)
{
	ResetInvaders();
}
//---------------------------------------------------------------------------

void TGameForm::ResetInvaders()
{
	invader1->Top = FIRST_ROW_TOP; invader1->Left = 350;
	invader2->Top = FIRST_ROW_TOP; invader2->Left = 550;
	invader3->Top = FIRST_ROW_TOP; invader3->Left = 750;
	invader4->Top = SECOND_ROW_TOP; invader4->Left = 250;
	invader5->Top = SECOND_ROW_TOP; invader5->Left = 450;
	invader6->Top = SECOND_ROW_TOP; invader6->Left = 650;
	invader7->Top = SECOND_ROW_TOP; invader7->Left = 850;
	invader8->Top = THIRD_ROW_TOP; invader8->Left = 350;
	invader9->Top = THIRD_ROW_TOP; invader9->Left = 550;
	invader10->Top = THIRD_ROW_TOP; invader10->Left = 750;

	playerShip->Top = 440;
	playerShip->Left = 280;

}

void TGameForm::StartGame(int speed)
{
	gameSpeed = speed;

	btnStartEasy->Visible = false;
	btnStartHard->Visible = false;
	lblTitle->Visible = false;
	lblDifficulty->Visible = false;

	gameTimer->Enabled = true;
	invadersTimer->Enabled = true;

	bullet->Visible = false;

	// Make all invaders visible
	background->Visible = true;

	invader1->Visible = true;
	invader2->Visible = true;
	invader3->Visible = true;
	invader4->Visible = true;
	invader5->Visible = true;
	invader6->Visible = true;
	invader7->Visible = true;
	invader8->Visible = true;
	invader9->Visible = true;
	invader10->Visible = true;

	playerShip->Visible = true;
}


void __fastcall TGameForm::btnStartEasyClick(TObject *Sender)
{
	StartGame(EASY_SPEED);
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::btnStartHardClick(TObject *Sender)
{
	StartGame(HARD_SPEED);
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::gameTimerTimer(TObject *Sender)
{
	// Check win condition
	if (invadersRemaining <= 0)
	{
		EndGame(true);
		return;
	}

	// Check lose condition (collision with any invader)
	if (IsCollision(invader1, playerShip) || IsCollision(invader2, playerShip) ||
		IsCollision(invader3, playerShip) || IsCollision(invader4, playerShip) ||
		IsCollision(invader5, playerShip) || IsCollision(invader6, playerShip) ||
		IsCollision(invader7, playerShip) || IsCollision(invader8, playerShip) ||
		IsCollision(invader9, playerShip) || IsCollision(invader10, playerShip))
	{
		EndGame(false);
		return;
	}

	// Hide explosions when timer is off
	if (!explosionTimer->Enabled)
	{
		explosion->Visible = false;
	}

	// Check for hits on each invader
	CheckInvaderHit(bullet, invader1);
	CheckInvaderHit(bullet, invader2);
	CheckInvaderHit(bullet, invader3);
	CheckInvaderHit(bullet, invader4);
	CheckInvaderHit(bullet, invader5);
	CheckInvaderHit(bullet, invader6);
	CheckInvaderHit(bullet, invader7);
	CheckInvaderHit(bullet, invader8);
	CheckInvaderHit(bullet, invader9);
	CheckInvaderHit(bullet, invader10);
}
//---------------------------------------------------------------------------

void TGameForm::CheckInvaderHit(TImage* bullet, TImage* invader)
{
	if (IsHit(bullet, invader) && invader->Visible)
	{
		explosion->Top = invader->Top;
		explosion->Left = invader->Left + 8;
		bullet->Visible = false;
		invader->Visible = false;
		explosion->Visible = true;
		sndPlaySound(L"wav\\boom.wav", SND_ASYNC);
		explosionTimer->Enabled = true;
		invadersRemaining--;
	}
}

void __fastcall TGameForm::invadersTimerTimer(TObject *Sender)
{
	// Move all invaders
	invader1->Left += gameSpeed;
	invader2->Left += gameSpeed;
	invader3->Left += gameSpeed;
	invader4->Left += gameSpeed;
	invader5->Left += gameSpeed;
	invader6->Left += gameSpeed;
	invader7->Left += gameSpeed;
	invader8->Left += gameSpeed;
	invader9->Left += gameSpeed;
	invader10->Left += gameSpeed;

	// Check if invaders need to change direction and drop down
	if (invader7->Left >= background->Width - 10 || invader4->Left <= background->Left + 10)
	{
		// Drop all invaders down
		invader1->Top += INVADER_DROP;
		invader2->Top += INVADER_DROP;
		invader3->Top += INVADER_DROP;
		invader4->Top += INVADER_DROP;
		invader5->Top += INVADER_DROP;
		invader6->Top += INVADER_DROP;
		invader7->Top += INVADER_DROP;
		invader8->Top += INVADER_DROP;
		invader9->Top += INVADER_DROP;
		invader10->Top += INVADER_DROP;

		// Reverse direction
		gameSpeed = -gameSpeed;
	}
}
//---------------------------------------------------------------------------

void TGameForm::EndGame(bool playerWon)
{
	gameTimer->Enabled = false;
	invadersTimer->Enabled = false;
	bulletTimer->Enabled = false;
	moveLeftTimer->Enabled = false;
	moveRightTimer->Enabled = false;

	//background->Visible = false;
	lblTitle->Caption = playerWon ? "You Win! Play Again?" : "Game Over! Try Again?";
	lblTitle->Font->Color = clWhite;
	lblTitle->Visible = true;
	btnRestart->Visible = true;
}
void __fastcall TGameForm::explosionTimerTimer(TObject *Sender)
{
	if (explosionTimer->Enabled)
	{
		explosionTimer->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::moveLeftTimerTimer(TObject *Sender)
{
	if (playerShip->Left > 10)
		playerShip->Left -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::moveRightTimerTimer(TObject *Sender)
{
	if (playerShip->Left + playerShip->Width < background->Width - 10)
		playerShip->Left += 10;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::bulletTimerTimer(TObject *Sender)
{
	if (bullet->Top >= background->Top + 10)
	{
		bullet->Top -= 15;
	}
	else
	{
		bullet->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (!gameTimer->Enabled) return;

	if (Key == VK_RIGHT) moveRightTimer->Enabled = true;
	if (Key == VK_LEFT) moveLeftTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
	if (Key == VK_SPACE && !bullet->Visible && gameTimer->Enabled)
	{
		bullet->Left = playerShip->Left + playerShip->Width/2 - 20;
		bullet->Top = playerShip->Top;
		bullet->Visible = true;
		bulletTimer->Enabled = true;
		sndPlaySound(L"wav\\shot.wav", SND_ASYNC);
	}
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RIGHT) moveRightTimer->Enabled = false;
	if (Key == VK_LEFT) moveLeftTimer->Enabled = false;
}
//---------------------------------------------------------------------------

