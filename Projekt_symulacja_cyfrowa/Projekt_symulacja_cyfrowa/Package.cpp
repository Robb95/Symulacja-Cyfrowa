#include "Package.h"



Package::Package(int id_base_station,int id_package)
{
	id_base_station_ = id_base_station; 
	id_package_ = id_package;
	number_current_retransmission_ = 0;
}

int Package::ReturnNumberCurrentRetransmission()
{
	return number_current_retransmission_;
}

int Package::ReturnIdBaseStation()
{
	return id_base_station_;
}

void Package::IncrementLR()
{
	number_current_retransmission_++;
}

int Package::ReturnIdPackage()
{
  return id_package_;
}

void Package::SaveGeneratedTime(double time)
{
	time_generated_ = time;
}

void Package::SaveExitBuffor(double time)
{
	time_exit_buffor_ = time;
}

void Package::SaveReceivingTime(double time)
{
	time_receiving_ = time;
}

double Package::GetAvergeExitBuffor()
{
	return time_exit_buffor_-time_generated_;
}

double Package::GetAverageReceiving()
{
	return time_receiving_-time_generated_;
}
