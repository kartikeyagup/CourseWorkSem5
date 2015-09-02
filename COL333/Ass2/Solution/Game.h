#ifndef GAME_H
#define GAME_H

#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

bool CheckPalindrome(char*,int,int);
bool CheckValidPalin(char*,int,int);
int ScoreString(char*,int,int);

class Game
{
public:
	Game();
	Game(int,bool);

	int CalculateScore();
	int GetPresentScore();
	void ShowPresent();
	void Move(int,int,int,int);
	void AddNew(char,int,int);

private:
	char **Board;
	bool TypePlayer; // 0 for Order, 1 for Chaos
	int Dimension;
	int Pscore;
};

#endif