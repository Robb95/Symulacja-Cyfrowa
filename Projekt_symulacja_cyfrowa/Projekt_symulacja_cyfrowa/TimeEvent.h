#ifndef TIMEEVENT_H
#define TIMEEVENT_H
#include<iostream>
using namespace std;

class TimeEvent
{
public:
	virtual void Execute() = 0;
	virtual double GetTime()=0;
	virtual int ReturnId()=0;
	TimeEvent* next_;
	TimeEvent* previous_;
	virtual void Print()=0;
	virtual int ReturnIdBaseStation()=0;

};
#endif

