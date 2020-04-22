#include "Package.h"



Package::Package(int id_base_station)
{
	id_base_station_ = id_base_station; 
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
