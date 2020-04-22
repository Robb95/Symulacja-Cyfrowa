#ifndef CHECKINGTHESLOTBUSY_H
#define CHECKINGTHESLOTBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class CheckingTheSlotBusy
{
public:
	CheckingTheSlotBusy(WirelessNetwork* network);
	~CheckingTheSlotBusy();
	void Ececute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
	int PT_;
	
	
};
#endif

