#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule
{
public:
	Schedule();
	~Schedule();

private:
	int t; 
	int p;
	int k;
	float c;

	int ***schedule;
};

#endif