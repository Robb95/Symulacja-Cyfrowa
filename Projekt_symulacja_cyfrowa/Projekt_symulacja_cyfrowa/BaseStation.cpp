#include "BaseStation.h"

BaseStation::BaseStation()
{
	id_base_station_ = 0;
}

void BaseStation::AddToBaseStation(Package* packet)
{
	
	package_.push(packet);
}

void BaseStation::SetPackageToRetransmission(Package* get_package_to_retransmission)
{
	get_package_to_retransmission_ = get_package_to_retransmission;
}
