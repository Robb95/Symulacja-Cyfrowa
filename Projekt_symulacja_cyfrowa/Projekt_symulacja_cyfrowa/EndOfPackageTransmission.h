#ifndef ENDOFPACKAGETRANSMISSION_H
#define ENDOFPACKAGETRANSMISSION_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class EndOfPackageTransmission
{
public:
	EndOfPackageTransmission();
	~EndOfPackageTransmission();
	double GetTime();
	void Print();
private:
	double time_;
};
#endif

