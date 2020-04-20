#ifndef ERRORTER_H
#define ERRORTER_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class ErrorTER
{
public:
	ErrorTER();
	~ErrorTER();
	double GetTime();
	void Print();

private:
	double time_;
};
#endif
