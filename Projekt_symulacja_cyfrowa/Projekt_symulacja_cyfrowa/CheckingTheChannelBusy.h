#ifndef CHECKINGTHECHANNELBUSY_H
#define CHECKINGTHECHANNELBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
#include "TimeEventList.h"
#include "EndOfPackageTransmission.h"
#include "CheckAckMessage.h"
class CheckingTheChannelBusy :public TimeEvent
{
public:
	CheckingTheChannelBusy(WirelessNetwork* network,TimeEventList* list,int id_base_station,double time, bool first_check);
	~CheckingTheChannelBusy() = default;
	void Execute();
	double GetTime();
	void Print();
	int ReturnId();
	int ReturnIdBaseStation();
private:
	double time_;
	WirelessNetwork* network_;
	int PT_;
	int id_base_station_;
	TimeEventList* list_;
	TimeEvent* event_;
	bool first_check_;
	int time_temp_;
	int id_ = 2;

};
#endif

