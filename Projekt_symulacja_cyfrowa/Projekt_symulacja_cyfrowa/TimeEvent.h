#ifndef TIMEEVENT_H
#define TIMEEVENT_H
#include<iostream>
using namespace std;

class TimeEvent
{
public:
	virtual void Execute() = 0;
	virtual double GetTime()=0;
	TimeEvent* next;
	TimeEvent* previous;
	virtual void Print()=0;

};
#endif
