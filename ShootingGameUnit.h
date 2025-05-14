//---------------------------------------------------------------------------

#ifndef ShootingGameUnitH
#define ShootingGameUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TGameForm : public TForm
{
__published:	// IDE-managed Components
	TImage *background;
	TLabel *lblDifficulty;
	TButton *btnStartEasy;
	TButton *btnStartHard;
	TButton *btnRestart;
	TTimer *explosionTimer;
	TTimer *moveRightTimer;
	TTimer *moveLeftTimer;
	TTimer *bulletTimer;
	TTimer *invadersTimer;
	TTimer *gameTimer;
	TImage *invader1;
	TImage *invader10;
	TImage *invader2;
	TImage *invader3;
	TImage *invader4;
	TImage *invader5;
	TImage *invader6;
	TImage *invader7;
	TImage *invader8;
	TImage *invader9;
	TImage *explosion;
	TImage *playerShip;
	TImage *bullet;
	TLabel *lblTitle;
	void __fastcall btnStartEasyClick(TObject *Sender);
	void __fastcall btnStartHardClick(TObject *Sender);
	void __fastcall gameTimerTimer(TObject *Sender);
	void __fastcall invadersTimerTimer(TObject *Sender);
	void __fastcall explosionTimerTimer(TObject *Sender);
	void __fastcall moveLeftTimerTimer(TObject *Sender);
	void __fastcall moveRightTimerTimer(TObject *Sender);
	void __fastcall bulletTimerTimer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TGameForm(TComponent* Owner);

	void InitializeGame();
	void ResetInvaders();
	void StartGame(int speed);
	void CheckInvaderHit(TImage* bullet, TImage* invader);
	void EndGame(bool playerWon);
};
//---------------------------------------------------------------------------
extern PACKAGE TGameForm *GameForm;
//---------------------------------------------------------------------------
#endif
