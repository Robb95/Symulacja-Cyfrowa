#include "BaseStation.h"

BaseStation::BaseStation(int id)
{
	id_base_station_ = id;
	ACK_message_ = false;
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
	if (get_package_to_retransmission_ == nullptr)
	{
		temp_package_ = package_.front();
		package_.pop();
		return temp_package_;
	}
	else
	{
		temp_package_ = get_package_to_retransmission_;
		get_package_to_retransmission_ = nullptr;
		return temp_package_;
	}
}

void BaseStation::SetAckMessage()
{
	ACK_message_ = true;
}

bool BaseStation::GetAckMessage()
{
	temp_ = ACK_message_;
	ACK_message_ = false;
	return temp_;
}

bool BaseStation::TheBuforIsEmpty()
{
	return package_.empty();
}


