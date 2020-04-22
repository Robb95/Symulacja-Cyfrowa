#include "ReceivingStation.h"



ReceivingStation::ReceivingStation(int id)
{
	id_receiving_station_ = id;
}

void ReceivingStation::EndOfTransmitting(Package* receiving_package)
{
	receiving_package_ = receiving_package;
}

int ReceivingStation::AddACK()
{
	return id_receiving_station_;
}
