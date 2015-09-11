#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

extern std::unordered_map<std::string,float> PalidromeScoreData;
extern char**Board;

bool CheckPalindrome(char*,int,int);
bool CheckValidPalin(char*,int,int);
int ScoreString(char*,int,int);
int GetEntireScore(char*,int);

struct OrderMove
{
	int initx, inity, finx, finy;
};

struct ChaosMove
{
	int posx,posy;
	char color;
};

class Game
{
public:
	Game();
	Game(int,bool);
	Game(int,bool,float,int,int*);

	~Game();

	int GetDimension();
	bool GetType();
	char* GetColumn(int);
	float GetPresentScore();
	int GetNumCompleted();
	int *GetColCompleted();

	int CalculateScore();
	void ShowPresent();
	void Move(int,int,int,int);
	void AddNew(char,int,int);
	float GetNewScoreInsert(char,int,int);
	float GetNewScoreMove(int,int,int,int);
	bool IsCompleted();
	bool GetValidMoveInsert(char,int,int);
	bool GetValidMoveShift(int,int,int,int);
	float *GetProbabilities();

	void MoveOrder(OrderMove&);
	void MoveChaos(ChaosMove&);
	void UndoMoveOrder(OrderMove&);
	void UndoMoveChaos(ChaosMove&);

private:
	bool TypePlayer; // 0 for Order, 1 for Chaos
	int Dimension;
	float Pscore;
	int NumCompleted;
	int *ColCompleted;
};

Game* GetDuplicate(Game*);
std::pair<int,int> GetDifferenceInsert(Game*,Game*);
std::pair<std::pair<int,int>,std::pair<int,int> > GetDifferenceMove(Game*,Game*);

#endif