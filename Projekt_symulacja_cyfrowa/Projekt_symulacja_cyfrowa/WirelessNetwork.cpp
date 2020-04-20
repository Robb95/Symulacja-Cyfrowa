#include "WirelessNetwork.h"

WirelessNetwork::WirelessNetwork()
{
	for (int i = 0; i < kNumberOfStations; i++)
	{
		BaseStation* base_station_tmp = new BaseStation();
		base_stations_.push_back(base_station_tmp);
	}

	for (int i = 0; i < kNumberOfStations; i++)
	{
		ReceivingStation* receiving_station_tmp = new ReceivingStation();
		receiving_station_.push_back(receiving_station_tmp);
	}

	channel_ = new Channel();
	system_time_ = 0;
}

void WirelessNetwork::GenerateSentPackage(Package* packet, int id_base_station)
{
	base_stations_[id_base_station]->AddToBaseStation(packet);
}

int WirelessNetwork::ReturnkAmountOfRetransmision()
{
	return kAmountOfRetransmission;
}

Channel* WirelessNetwork::ReturnChannel()
{
	return channel_;
}

void WirelessNetwork::SentPackageToRetransmission(Package* get_package_to_retransmission)
{
	base_stations_[get_package_to_retransmission->ReturnIdBaseStation()]->SetPackageToRetransmission(get_package_to_retransmission);
}





