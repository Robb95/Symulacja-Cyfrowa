#include "BaseStation.h"

BaseStation::BaseStation()
{
	id_base_station_ = 0;
}

void BaseStation::AddToBaseStation(Package* packet)
{
	
	package_.push(packet);
}
