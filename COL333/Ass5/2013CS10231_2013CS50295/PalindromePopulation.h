#ifndef PALINDROME_POPULATION_H
#define PALINDROME_POPULATION_H

#include "Game.h"
#include <queue>
#include <vector>
#include <cmath>
#include <fstream>

extern std::vector<std::string> AllStrings;
extern std::vector<float> NormalPalindromeScores;
extern int GlobalGameDim;

void Initialise(bool);
void PopulateTable(bool);
float PopulateTable1(const std::string &);
void PopulateAllTables(bool);
float GetRonakHeuristic(const std::string &);

#endif