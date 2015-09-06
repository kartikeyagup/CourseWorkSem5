#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

bool CheckPalindrome(char*,int,int);
bool CheckValidPalin(char*,int,int);
int ScoreString(char*,int,int);
int GetEntireScore(char*,int);

class Game
{
public:
	Game();
	Game(int,bool);
	Game(int,bool,char**,char**,int,int,int*);

	int GetDimension();
	bool GetType();
	char** GetBoard();
	char** GetBoardT();
	int GetPresentScore();
	int GetNumCompleted();
	int *GetColCompleted();

	int CalculateScore();
	void ShowPresent();
	void Move(int,int,int,int);
	void AddNew(char,int,int);
	int GetNewScoreInsert(char,int,int);
	int GetNewScoreMove(int,int,int,int);
	bool IsCompleted();
	bool GetValidMoveInsert(char,int,int);
	bool GetValidMoveShift(int,int,int,int);
	float *GetProbabilities();

private:
	char **Board;
	char **BoardT;
	bool TypePlayer; // 0 for Order, 1 for Chaos
	int Dimension;
	int Pscore;
	int NumCompleted;
	int *ColCompleted;
};

Game* GetDuplicate(Game*);

#endif