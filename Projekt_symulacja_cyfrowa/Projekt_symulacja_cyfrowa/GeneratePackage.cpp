#include "GeneratePackage.h"

GeneratePackage::GeneratePackage(WirelessNetwork* network, double time,int id_base_station, TimeEventList* event)
{
	network_ = network;
	time_ = time;
	id_base_station_ = id_base_station;
	event_ = event;
	
}

void GeneratePackage::Execute()
{
	Package* packet = new Package();
	network_->GenerateSentPackage(packet,id_base_station_);
	TimeEvent* genarte_new_package = new GeneratePackage(network_, 5, id_base_station_, event_);
	event_->AddTimeEvent(genarte_new_package);

}

double GeneratePackage::GetTime()
{
	return time_;
}

void GeneratePackage::Print()
{
	cerr << " Generate package: "<< time_ << endl;
}
