#ifndef CHECKINGTHECHANNELBUSY_H
#define CHECKINGTHECHANNELBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class CheckingTheChannelBusy
{
public:
	CheckingTheChannelBusy(WirelessNetwork* network,int id_base_station);
	~CheckingTheChannelBusy();
	void Execute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
	int PT_;
	int id_base_station_;
};
#endif

