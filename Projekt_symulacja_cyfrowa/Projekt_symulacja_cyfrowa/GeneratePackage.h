#ifndef GENERATEPACKAGE_H
#define GENERATEPACKAGE_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
#include "TimeEventList.h"
class GeneratePackage: public TimeEvent
{
public:
	GeneratePackage(WirelessNetwork* network,double time, int id_base_station, TimeEventList* event);
	~GeneratePackage();
	void Execute();
	double GetTime();
	void Print();
private:
	double time_;
	WirelessNetwork* network_;
	int id_base_station_;
	TimeEventList* event_;
};
#endif
