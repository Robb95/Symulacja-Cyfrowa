#ifndef ENDOFPACKAGETRANSMISSION_H
#define ENDOFPACKAGETRANSMISSION_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class EndOfPackageTransmission
{
public:
	EndOfPackageTransmission(WirelessNetwork* network);
	~EndOfPackageTransmission();
	void Execute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
};
#endif

