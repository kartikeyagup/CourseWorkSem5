#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

extern char* vert;
extern std::unordered_map<std::string,float> PalidromeScoreData;
extern std::unordered_map<std::string,float>* AllPalindromesData;

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
	Game(int,bool,char**,float,int,int*);

	~Game();

	int GetDimension();
	bool GetType();
	char* GetColumn(int);
	char** GetBoard();
	float GetPresentScore();
	int GetNumCompleted();
	int *GetColCompleted();
	float GetEntireScore2(int);
	std::pair<int,int> GetRandomMoveChaos();
	std::pair<std::pair<int,int>, std::pair<int,int> > GetRandomMoveOrder();

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

	float MoveOrder(OrderMove*);
	float MoveChaos(ChaosMove*);
	float MoveAndUndoOrder(OrderMove*);
	float UndoMoveOrder(OrderMove*);
	float UndoMoveChaos(ChaosMove*);
	float MoveAndUndoChaos(ChaosMove*);

private:
	bool TypePlayer; // 0 for Order, 1 for Chaos
	int Dimension;
	char **Board;
	float Pscore;
	int NumCompleted;
	int *ColCompleted;
};

Game* GetDuplicate(Game*);
std::pair<int,int> GetDifferenceInsert(Game*,Game*);
std::pair<std::pair<int,int>,std::pair<int,int> > GetDifferenceMove(Game*,Game*);

#endif