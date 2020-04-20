#ifndef CHECKINGCHANNELSTATUSAFTERTRANSMISSION_H
#define CHECKINGCHANNELSTATUSAFTERTRANSMISSION_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class CheckingChannelStatusAfterRetransmission:public TimeEvent
{
public:
	CheckingChannelStatusAfterRetransmission();
	~CheckingChannelStatusAfterRetransmission();
	double GetTime();
	void Print();

private:
	double time_;
};
#endif

