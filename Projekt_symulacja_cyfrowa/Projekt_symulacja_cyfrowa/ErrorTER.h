#ifndef ERRORTER_H
#define ERRORTER_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
#include "Channel.h"
#include "Package.h"
class ErrorTER:public TimeEvent
{
public:
	ErrorTER(WirelessNetwork* network);
	~ErrorTER();
	double GetTime();
	void Print();
	void Execute();

private:
	double time_;
	WirelessNetwork* network_;
};
#endif
