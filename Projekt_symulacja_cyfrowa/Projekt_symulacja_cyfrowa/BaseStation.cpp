#include "BaseStation.h"

BaseStation::BaseStation(int id)
{
	id_base_station_ = id;
}

void BaseStation::AddToBaseStation(Package* packet)
{
	
	package_.push(packet);
}

void BaseStation::SetPackageToRetransmission(Package* get_package_to_retransmission)
{
	get_package_to_retransmission_ = get_package_to_retransmission;
}

Package* BaseStation::SentPackageBaseStationToReceivingStation()
{
	tmp= package_.front();
	package_.pop();
	return tmp;
}
