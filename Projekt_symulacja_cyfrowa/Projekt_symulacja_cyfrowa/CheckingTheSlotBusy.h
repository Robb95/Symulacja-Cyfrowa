#ifndef CHECKINGTHESLOTBUSY_H
#define CHECKINGTHESLOTBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class CheckingTheSlotBusy
{
public:
	CheckingTheSlotBusy();
	~CheckingTheSlotBusy();
	double GetTime();
	void Print();
private:
	double time_;
};
#endif

