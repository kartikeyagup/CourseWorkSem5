#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "Schedule.h"

class TimeTable
{
public:
	TimeTable();
	~TimeTable();
private:
	Schedule ScheduleParameters;
	int ***ordering;
};

#endif