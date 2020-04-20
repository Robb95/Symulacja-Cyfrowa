#ifndef CHECKINGTHECHANNELBUSY_H
#define CHECKINGTHECHANNELBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class CheckingTheChannelBusy
{
public:
	CheckingTheChannelBusy();
	~CheckingTheChannelBusy();
	double GetTime();
	void Print();
private:
	double time_;
};
#endif

