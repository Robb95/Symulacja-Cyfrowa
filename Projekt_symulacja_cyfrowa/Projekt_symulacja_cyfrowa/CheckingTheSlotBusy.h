#ifndef CHECKINGTHESLOTBUSY_H
#define CHECKINGTHESLOTBUSY_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
#include "CheckingTheChannelBusy.h"
#include "TimeEventList.h"
#include "EndOfPackageTransmission.h"
#include "CheckAckMessage.h"
class CheckingTheSlotBusy: public TimeEvent
{
public:
	CheckingTheSlotBusy(WirelessNetwork* network,double time, TimeEventList* list);
	~CheckingTheSlotBusy() = default;
	void Execute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
	TimeEventList* list_;
	int PT_;
	TimeEvent* event_;
	unsigned size_of_vector_;
	int id_actual_element_;
	double time_temp_;
};
#endif

