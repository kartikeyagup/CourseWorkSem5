#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string,int> PalidromeScoreData;

bool CheckPalindrome(char*,int,int);
bool CheckValidPalin(char*,int,int);
int ScoreString(char*,int,int);
int GetEntireScore(char*,int);

class Game
{
public:
	Game();
	Game(int,bool);
	Game(int,bool,char**,char**,float,int,int*);

	~Game();

	int GetDimension();
	bool GetType();
	char** GetBoard();
	char** GetBoardT();
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

private:
	char **Board;
	char **BoardT;
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