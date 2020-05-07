#ifndef ENDOFPACKAGETRANSMISSION_H
#define ENDOFPACKAGETRANSMISSION_H
#include "TimeEvent.h";
#include "WirelessNetwork.h"
#include "Channel.h"
#include "Package.h"
#include "FinishSendingAckChannel.h"
#include "TimeEventList.h"
class EndOfPackageTransmission: public TimeEvent
{
public:
	EndOfPackageTransmission(WirelessNetwork* network, TimeEventList* list,double time);
	~EndOfPackageTransmission() = default;
	void Execute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
	Channel* channel_;
	TimeEvent* event_;
	TimeEventList* list_;
	int temp_;
	Package* package_;
	int id_base_station_;

};
#endif

