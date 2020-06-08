#include "BaseStation.h"
#include <iostream>
using namespace std;
BaseStation::BaseStation(int id)
{
	id_base_station_ = id;
	ACK_message_ = false;
	error_rate_=0;
	all_rate_=0;
}

void BaseStation::AddToBaseStation(Package* packet)
{
	
	package_.push(packet);
}

void BaseStation::SetPackageToRetransmission(Package* get_package_to_retransmission)
{
	get_package_to_retransmission_ = get_package_to_retransmission;
}

Package* BaseStation::SentPackageBaseStationToReceivingStation(double time)
{
	if (get_package_to_retransmission_ == nullptr)
	{
		temp_package_ = package_.front();
		package_.pop();
		temp_package_->SaveExitBuffor(time);
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

double BaseStation::GetAverageErrorRate()
{
	//cerr << "id: " << this->id_base_station_ << " error rate: " << error_rate_ << " all rate " << all_rate_ << endl;
	if (error_rate_ == 0)return 0;
		return error_rate_ / all_rate_;
}

void BaseStation::ResetStatistic()
{
	error_rate_ = 0;
	all_rate_ = 0;
}

void BaseStation::AddErorRate()
{
	error_rate_++;
}

void BaseStation::AddAllRate()
{
	all_rate_++;
}




