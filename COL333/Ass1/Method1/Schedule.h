#ifndef SCHEDULE_H
#define SCHEDULE_H

using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>

#include "Util.h"


struct ScheduleParams
{
	int k; // Papers in session
	int p; // parallel sessions
	int t; // time slots
	double c;
	int tp;
	int pk;
	double **d;
};

class Schedule
{
public:
	Schedule();
	Schedule(std::string);

	float GetHappiness(int *);
	void ShowSchedule();
	void NormalDFS();
	void RandomMovement();
	void SwapIJ(int,int);

private:
	double processtime;
	float presentgoodness;
	ScheduleParams Sp;
	int totalpapers;
	int *schedule;
};

#endif