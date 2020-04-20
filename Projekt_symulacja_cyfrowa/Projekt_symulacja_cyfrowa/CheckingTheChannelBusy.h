#ifndef CHECKINGTHECHANNELBUSY_H
#define CHECKINGTHECHANNELBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class CheckingTheChannelBusy
{
public:
	CheckingTheChannelBusy(WirelessNetwork* network);
	~CheckingTheChannelBusy();
	void Execute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
};
#endif

